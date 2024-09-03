#include "DisplayWidget.h"
#include <wayland-egl.h>
#include "glad/egl.h"

struct Version
{
    int major_version;
    int minor_version;
};

struct WindowInfo
{
    /// Connection to the display server. On most platforms except X11/Wayland, this is implicit and null.
    void *display_connection = nullptr;

    /// Abstract handle to the window. This depends on the surface type.
    void *window_handle = nullptr;

    /// For platforms where a separate surface/layer handle is needed, it is stored here (e.g. MacOS).
    void *surface_handle = nullptr;

    /// Width of the surface in pixels.
    uint32_t surface_width = 0;

    /// Height of the surface in pixels.
    uint32_t surface_height = 0;

    /// DPI scale for the surface.
    float surface_scale = 1.0f;

    /// Refresh rate of the surface, if available.
    float surface_refresh_rate = 0.0f;
};

class GLContextEGL
{

protected:
    EGLDisplay m_display = EGL_NO_DISPLAY;
    EGLSurface m_surface = EGL_NO_SURFACE;
    EGLContext m_context = EGL_NO_CONTEXT;

    EGLConfig m_config = {};

    GLContextEGL();
    ~GLContextEGL();

    bool InitGL();
    bool CreateContext(const Version &version, EGLContext share_context);
    bool CheckConfigSurfaceFormat(EGLConfig config);
    bool CreateSurface();
    EGLSurface CreateFallbackSurface(EGLConfig config, void *window);
    EGLSurface TryCreatePlatformSurface(EGLConfig config, void *window);
    EGLSurface CreateWLSurface(EGLConfig config, void *win);
    bool LoadModule();

    bool m_use_ext_platform_base = false;
    bool m_supports_negative_swap_interval = false;

    Version m_version = {};

    // Wayland window or surface stuffs

    WindowInfo m_wi;
    wl_egl_window *m_wl_window = nullptr;

    void *m_wl_module = nullptr;
    wl_egl_window *(*m_wl_egl_window_create)(struct wl_surface *surface, int width, int height);
    void (*m_wl_egl_window_destroy)(struct wl_egl_window *egl_window);
    void (*m_wl_egl_window_resize)(struct wl_egl_window *egl_window, int width, int height, int dx, int dy);
};