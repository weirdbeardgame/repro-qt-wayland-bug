#include "InitialWidget.h"

#include <QStackedWidget>
#include <QListWidget>

InitialWidget::InitialWidget(QWidget* parent)
	: QWidget(parent)
{
	// Create a stack widget that fills the entire window
	ui.setupUi(this);

	QListWidget* listWidget = new QListWidget(this);
	listWidget->setStyleSheet("background-color: #fff0f0;");

	// fill initialWidget with some items
	for (int i = 0; i < 100; i++)
	{
		listWidget->addItem(QString("Item %1").arg(i));
	}
	ui.stackedWidget->insertWidget(0,listWidget);
}

InitialWidget::~InitialWidget()
{
}

