#include "mainwindow.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCoreApplication::setApplicationName("Circuit Editor");
	QSettings settings;
	MainWindow w;
	w.setWindowTitle("Circuit Editor");
	w.show();

	return a.exec();
}
