#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	initialWidget = new QListWidget(this);
	// set background color
	initialWidget->setStyleSheet("background-color: #fff0f0;");

	// fill initialWidget with some items
	for (int i = 0; i < 100; i++)
	{
		initialWidget->addItem(QString("Item %1").arg(i));
	}

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
		replacementWidget = new QListWidget(this);
		replacementWidget->setStyleSheet("background-color: #f0fff0;");
		for(int i = 99; i >= 0; i--)
		{
			replacementWidget->addItem(QString("Item %1").arg(i));
		}
	}

	setCentralWidget(replacementWidget);
	replacementWidget->setFocus();
}

void MainWindow::on_actionAttach_triggered()
{
	takeCentralWidget();
	initialWidget->setVisible(true);
	
	replacementWidget->deleteLater();
	replacementWidget = nullptr;

	setCentralWidget(initialWidget);
	initialWidget->show();
	initialWidget->setFocus();
}
