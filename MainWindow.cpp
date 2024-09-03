#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  ui.setupUi(this);

  initialWidget = new InitialWidget(this);
  initialWidget->setStyleSheet("background-color: #f0f0ff;");
  setCentralWidget(initialWidget);
}

MainWindow::~MainWindow() {}

QWidget *MainWindow::getContentParent() 
{
  return s_use_central_widget ? static_cast<QWidget *>(this): static_cast<QWidget *>(initialWidget);
}

void MainWindow::on_actionDetach_triggered() {

  initialWidget->setVisible(false);
  takeCentralWidget();
  initialWidget->setParent(this);

  setCentralWidget(replacementWidget);

  update();
}

void MainWindow::on_actionAttach_triggered() {
  takeCentralWidget();
  initialWidget->setVisible(true);

  // replacementWidget->deleteLater();
  replacementWidget = nullptr;

  setCentralWidget(initialWidget);
  initialWidget->show();
  update();

}

void MainWindow::createDisplayWidget(bool fullscreen, bool render_to_main) {
  QWidget *container;

  displayWidget = new DisplayWidget((!fullscreen && render_to_main) ? getContentParent() : nullptr);
  container = displayWidget;

  if (fullscreen || !render_to_main) {
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