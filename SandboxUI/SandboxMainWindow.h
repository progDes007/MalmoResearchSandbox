#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SandboxMainWindow.h"

class SandboxMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	SandboxMainWindow(QWidget *parent = Q_NULLPTR);

private:
	Ui::SandboxMainWindowClass ui;
};
