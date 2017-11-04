#include "Internal.h"
#include "SandboxMainWindow.h"
#include "Agent/Agent.h"

#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SandboxMainWindow w;
	w.show();

	// Create the agent
	Agent agent;

	return a.exec();
}
