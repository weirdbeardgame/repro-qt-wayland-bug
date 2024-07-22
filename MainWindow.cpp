#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	initialWidget = new InitialWidget(this);
	initialWidget->setStyleSheet("background-color: #f0f0ff;");
	setCentralWidget(initialWidget);
}

MainWindow::~MainWindow()
{
}


void MainWindow::on_actionDetach_triggered()
{
	initialWidget->setVisible(false);
	takeCentralWidget();
	initialWidget->setParent(this);

	if(replacementWidget == nullptr)
	{
		replacementWidget = new ReplacementWidget(this);
	}

	setCentralWidget(replacementWidget);
	replacementWidget->setFocus();
	update();
}

void MainWindow::on_actionAttach_triggered()
{
	takeCentralWidget();
	initialWidget->setVisible(true);
	
	//replacementWidget->deleteLater();
	replacementWidget = nullptr;

	setCentralWidget(initialWidget);
	initialWidget->show();
	update();
}
