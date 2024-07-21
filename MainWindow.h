#pragma once

#include <QMainWindow>
#include <QListWidget>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void on_actionDetach_triggered();
	void on_actionAttach_triggered();

private:
	Ui::MainWindow ui;

	QListWidget *initialWidget;
	QListWidget *replacementWidget = nullptr;
};
