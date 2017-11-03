#include "SandboxMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SandboxMainWindow w;
	w.show();
	return a.exec();
}
