#include "Internal.h"
#include "SandboxMainWindow.h"


struct SandboxMainWindow::Impl 
{
};

/////////////////////////////////////////////////////////////////
SandboxMainWindow::SandboxMainWindow(QWidget *parent)
	: QMainWindow(parent), m_impl(new Impl)
{
	ui.setupUi(this);

}

SandboxMainWindow::~SandboxMainWindow()
{}