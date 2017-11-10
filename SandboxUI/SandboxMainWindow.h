#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SandboxMainWindow.h"

class SandboxMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	SandboxMainWindow(QWidget *parent = Q_NULLPTR);
	virtual ~SandboxMainWindow();
protected slots:
	void onTest1();
private:
	struct Impl;
	Ui::SandboxMainWindowClass ui;
	std::unique_ptr<Impl> m_impl;
};
