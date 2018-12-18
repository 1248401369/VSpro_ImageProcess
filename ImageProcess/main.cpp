#include "ImageProcess.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
	QApplication a(argc, argv);
	ImageProcess w;
	w.show();
	return a.exec();
}
