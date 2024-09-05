#include "GLContextEGL.h"
#include <dlfcn.h>
#include "fmt/format.h"

static DynamicLibrary s_egl_library;

static std::atomic_uint32_t s_egl_refcount = 0;

static const char *WAYLAND_EGL_MODNAME = "libwayland-egl.so.1";

void *DynamicLibrary::GetSymbolAddress(const char *name) const
{
#ifdef _WIN32
    return reinterpret_cast<void *>(GetProcAddress(reinterpret_cast<HMODULE>(m_handle), name));
#else
    return reinterpret_cast<void *>(dlsym(m_handle, name));
#endif
}

std::string DynamicLibrary::GetVersionedFilename(const char *libname, int major, int minor)
{

    const char *prefix = std::strncmp(libname, "lib", 3) ? "lib" : "";
    if (major >= 0 && minor >= 0)
        return fmt::format("{}{}.so.{}.{}", prefix, libname, major, minor);
    else if (major >= 0)
        return fmt::format("{}{}.so.{}", prefix, libname, major);
    else
        return fmt::format("{}{}.so", prefix, libname);
}

bool DynamicLibrary::Open(const char *filename)
{
    m_handle = dlopen(filename, RTLD_NOW);

    return m_handle != nullptr;
}

bool GLContextEGL::LoadEGL()
{
    // We're not going to be calling this from multiple threads concurrently.
    // So, not wrapping this in a mutex should be fine.
    if (s_egl_refcount.fetch_add(1, std::memory_order_acq_rel) == 0)
    {
        std::string egl_libname = DynamicLibrary::GetVersionedFilename("libEGL");
        printf("Loading EGL from {}...", egl_libname);

        if (!s_egl_library.Open(egl_libname.c_str()))
        {
            // Try versioned.
            egl_libname = DynamicLibrary::GetVersionedFilename("libEGL", 1);
            printf("Loading EGL from {}...", egl_libname);
            if (!s_egl_library.Open(egl_libname.c_str()))
                return false;
        }
    }

    return s_egl_library.IsOpen();
}

bool GLContextEGL::LoadGLADEGL(EGLDisplay display)
{
    const int version =
        gladLoadEGL(display, [](const char *name)
                    { return (GLADapiproc)s_egl_library.GetSymbolAddress(name); });
    if (version == 0)
    {
        return false;
    }

    return true;
}

bool GLContextEGL::CheckConfigSurfaceFormat(EGLConfig config)
{
    int red_size, green_size, blue_size, alpha_size;
    if (!eglGetConfigAttrib(m_display, config, EGL_RED_SIZE, &red_size) ||
        !eglGetConfigAttrib(m_display, config, EGL_GREEN_SIZE, &green_size) ||
        !eglGetConfigAttrib(m_display, config, EGL_BLUE_SIZE, &blue_size) ||
        !eglGetConfigAttrib(m_display, config, EGL_ALPHA_SIZE, &alpha_size))
    {
        return false;
    }

    return (red_size == 8 && green_size == 8 && blue_size == 8);
}

bool GLContextEGL::CreateContext(const Version &version, EGLContext share_context)
{
    // custom int32 based type
    EGLint num_configs;

    const int surface_attribs[] = {
        EGL_RENDERABLE_TYPE,
        EGL_OPENGL_BIT,
        EGL_SURFACE_TYPE,
        EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8, EGL_NONE, 0};

    if (!eglChooseConfig(m_display, surface_attribs, nullptr, 0, &num_configs) || num_configs == 0)
    {
        // printf("eglChooseConfig() failed: 0x{:x}", eglGetError());
        return false;
    }

    std::vector<EGLConfig> configs(static_cast<uint32_t>(num_configs));
    if (!eglChooseConfig(m_display, surface_attribs, configs.data(), num_configs, &num_configs))
    {
        // printf("eglChooseConfig() failed: 0x{:x}", eglGetError());
        return false;
    }
    configs.resize(static_cast<uint32_t>(num_configs));

    std::optional<EGLConfig> config;
    for (EGLConfig check_config : configs)
    {
        if (CheckConfigSurfaceFormat(check_config))
        {
            config = check_config;
            break;
        }
    }

    if (!config.has_value())
    {
        printf("No EGL configs matched exactly, using first.");
        config = configs.front();
    }

    const int attribs[] = {
        EGL_CONTEXT_MAJOR_VERSION,
        version.major_version,
        EGL_CONTEXT_MINOR_VERSION,
        version.minor_version,
        EGL_NONE,
        0};

    if (!eglBindAPI(EGL_OPENGL_API))
    {
        // printf("eglBindAPI() failed: 0x{:x}", eglGetError());
        return false;
    }

    m_context = eglCreateContext(m_display, config.value(), share_context, attribs);
    if (!m_context)
    {
        // printf("eglCreateContext() failed: 0x{:x}", eglGetError());
        return false;
    }

    // printf("Got GL version {}.{}", version.major_version, version.minor_version);

    EGLint min_swap_interval, max_swap_interval;
    m_supports_negative_swap_interval = false;
    if (eglGetConfigAttrib(m_display, config.value(), EGL_MIN_SWAP_INTERVAL, &min_swap_interval) &&
        eglGetConfigAttrib(m_display, config.value(), EGL_MAX_SWAP_INTERVAL, &max_swap_interval))
    {
        printf("EGL_MIN_SWAP_INTERVAL = {}", min_swap_interval);
        printf("EGL_MAX_SWAP_INTERVAL = {}", max_swap_interval);
        m_supports_negative_swap_interval = (min_swap_interval <= -1);
    }

    m_config = config.value();
    m_version = version;
    return true;
}

EGLSurface GLContextEGL::TryCreatePlatformSurface(EGLConfig config, void *win)
{
    EGLSurface surface = EGL_NO_SURFACE;
    if (m_use_ext_platform_base)
    {
        PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC create_platform_window_surface_ext =
            (PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC)eglGetProcAddress("eglCreatePlatformWindowSurfaceEXT");
        if (create_platform_window_surface_ext)
        {
            surface = create_platform_window_surface_ext(m_display, config, win, nullptr);
            if (surface == EGL_NO_SURFACE)
            {
                const EGLint err = eglGetError();
            }
        }
        else
        {
            printf("eglCreatePlatformWindowSurfaceEXT() not found");
        }
    }

    return surface;
}

EGLSurface GLContextEGL::CreateFallbackSurface(EGLConfig config, void *win)
{
    printf("Using fallback eglCreateWindowSurface() path.");

    EGLSurface surface = eglCreateWindowSurface(m_display, config, (EGLNativeWindowType)win, nullptr);
    if (surface == EGL_NO_SURFACE)
    {
        const EGLint err = eglGetError();
    }

    return surface;
}

EGLSurface GLContextEGL::CreateWLSurface(EGLConfig config, void *win)
{
    if (m_wl_window)
    {
        m_wl_egl_window_destroy(m_wl_window);
        m_wl_window = nullptr;
    }

    m_wl_window = m_wl_egl_window_create(static_cast<wl_surface *>(win), m_wi.surface_width, m_wi.surface_height);
    if (!m_wl_window)
    {
        return EGL_NO_SURFACE;
    }

    EGLSurface surface = TryCreatePlatformSurface(config, m_wl_window);
    if (surface == EGL_NO_SURFACE)
    {
        surface = CreateFallbackSurface(config, m_wl_window);
        if (surface == EGL_NO_SURFACE)
        {
            m_wl_egl_window_destroy(m_wl_window);
            m_wl_window = nullptr;
        }
    }

    return surface;
}

bool GLContextEGL::CreateSurface()
{

    m_surface = CreateWLSurface(m_config, m_wi.window_handle);
    if (m_surface == EGL_NO_SURFACE)
    {

        return false;
    }

    // Some implementations may require the size to be queried at runtime.
    EGLint surface_width, surface_height;
    if (eglQuerySurface(m_display, m_surface, EGL_WIDTH, &surface_width) &&
        eglQuerySurface(m_display, m_surface, EGL_HEIGHT, &surface_height))
    {
        m_wi.surface_width = static_cast<uint32_t>(surface_width);
        m_wi.surface_height = static_cast<uint32_t>(surface_height);
    }
    else
    {
        // printf("eglQuerySurface() failed: 0x{:x}", eglGetError());
    }

    return true;
}

bool GLContextEGL::InitGL()
{
    if (!LoadGLADEGL(EGL_NO_DISPLAY))
    {
        return false;
    }
}

bool GLContextEGL::LoadModule()
{
    m_wl_module = dlopen(WAYLAND_EGL_MODNAME, RTLD_NOW | RTLD_GLOBAL);
    if (!m_wl_module)
    {
        const char *err = dlerror();
        return false;
    }

    m_wl_egl_window_create =
        reinterpret_cast<decltype(m_wl_egl_window_create)>(dlsym(m_wl_module, "wl_egl_window_create"));
    m_wl_egl_window_destroy =
        reinterpret_cast<decltype(m_wl_egl_window_destroy)>(dlsym(m_wl_module, "wl_egl_window_destroy"));
    m_wl_egl_window_resize =
        reinterpret_cast<decltype(m_wl_egl_window_resize)>(dlsym(m_wl_module, "wl_egl_window_resize"));
    if (!m_wl_egl_window_create || !m_wl_egl_window_destroy || !m_wl_egl_window_resize)
    {
        return false;
    }

    return true;
}

GLContextEGL::~GLContextEGL()
{
    // DestroySurface();
    // DestroyContext();
    // UnloadEGL();
}
