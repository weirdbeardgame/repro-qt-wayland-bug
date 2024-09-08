#include "MainWindow.h"
#include "glad/gl.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    initialWidget = new InitialWidget(this);
    initialWidget->setStyleSheet("background-color: #f0f0ff;");
    setCentralWidget(initialWidget);
}

MainWindow::~MainWindow() {}

QWidget *MainWindow::getContentParent()
{
    return s_use_central_widget ? static_cast<QWidget *>(this) : static_cast<QWidget *>(initialWidget);
}

void MainWindow::on_actionDetach_triggered()
{

    initialWidget->setVisible(false);
    takeCentralWidget();
    initialWidget->setParent(this);

    createDisplayWidget(false, true);
    InitEGL();

    setCentralWidget(displayWidget);

    update();
}

void MainWindow::InitEGL()
{

    static GLContextEGL *local;

    // We need at least GL3.3.
    static constexpr Version vlist[] = {
        {4, 6},
        {4, 5},
        {4, 4},
        {4, 3},
        {4, 2},
        {4, 1},
        {4, 0},
        {3, 3},
    };

    eglContext = GLContextEGL::Create(wi, vlist);
    if (!eglContext)
    {
        return;
    }

    local = eglContext.get();

    if (!gladLoadGL([](const char *name)
                    { return reinterpret_cast<GLADapiproc>(local->GetProcAddress(name)); }))
    {
        printf("Failed to InitEGLContext!");
    }
}

void MainWindow::on_actionAttach_triggered()
{
    takeCentralWidget();
    initialWidget->setVisible(true);

    // replacementWidget->deleteLater();
    displayWidget = nullptr;

    setCentralWidget(initialWidget);
    initialWidget->show();
    update();
}

void MainWindow::createDisplayWidget(bool fullscreen, bool render_to_main)
{
    QWidget *container;

    displayWidget = new DisplayWidget((!fullscreen && render_to_main) ? getContentParent() : nullptr);
    container = displayWidget;

    if (fullscreen || !render_to_main)
    {
        container->setWindowTitle(windowTitle());
        container->setWindowIcon(windowIcon());
    }

    initialWidget->setVisible(false);

    takeCentralWidget();

    initialWidget->setParent(this);

    setCentralWidget(displayWidget);

    displayWidget->setFocus();

    update();
}