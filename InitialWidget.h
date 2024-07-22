#pragma once

#include <QtWidgets/QWidget>

#include "ui_InitialWidget.h"

class InitialWidget final : public QWidget
{
	Q_OBJECT

public:
	explicit InitialWidget(QWidget *parent);
	~InitialWidget();

private:
	Ui::InitialWidget ui;
};
