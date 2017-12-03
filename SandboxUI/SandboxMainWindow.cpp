#include "Internal.h"
#include "SandboxMainWindow.h"
#include "Missions.h"



struct SandboxMainWindow::Impl 
{
	std::unique_ptr<AgentWorker> m_currentAgentWorker;

	void killCurrentAgent();
};

void SandboxMainWindow::Impl::killCurrentAgent()
{
	if (m_currentAgentWorker)
	{
		m_currentAgentWorker->cancel();
		m_currentAgentWorker->join();
		m_currentAgentWorker.reset();
	}
}

/////////////////////////////////////////////////////////////////
SandboxMainWindow::SandboxMainWindow(QWidget *parent)
	: QMainWindow(parent), m_impl(new Impl)
{
	ui.setupUi(this);

	// COnnect ui slots
	connect(ui.actionTest1, SIGNAL(triggered()), this, SLOT(onTest1()));
}

SandboxMainWindow::~SandboxMainWindow()
{
	m_impl->killCurrentAgent();
}

void SandboxMainWindow::onTest1()
{
	m_impl->killCurrentAgent();

	m_impl->m_currentAgentWorker = Missions::createMission1();
	m_impl->m_currentAgentWorker->startAsync();
}