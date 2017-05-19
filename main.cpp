#include "lecp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LECP w;
	w.show();

	return a.exec();
}