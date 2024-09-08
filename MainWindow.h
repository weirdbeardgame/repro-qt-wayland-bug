#pragma once

#include "ReplacementWidget.h"
#include "InitialWidget.h"
#include "DisplayWidget.h"
#include "GLContextEGL.h"

#include <QMainWindow>
#include <QListWidget>
#include <qwidget.h>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QWidget *getContentParent();

    static bool isNeeded(bool fullscreen, bool render_to_main);

    void createDisplayWidget(bool fullscreen, bool render_to_main);

    void removeDisplayWidget(bool show_game_list);

    void InitEGL();

    bool s_use_central_widget;

private slots:
    void on_actionDetach_triggered();
    void on_actionAttach_triggered();

private:
    Ui::MainWindow ui;

    WindowInfo wi;

    InitialWidget *initialWidget = nullptr;
    DisplayWidget *displayWidget = nullptr;

    std::unique_ptr<GLContextEGL> eglContext;
};
