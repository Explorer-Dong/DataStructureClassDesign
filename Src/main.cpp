#include <QApplication>
#include "Headers/SortWidget.h"
#include "Test/test2.cpp"

int main(int argc, char* argv[]) {
//	QApplication app(argc, argv);
//	SortWidget w;
//	w.show();
//	return app.exec();

	test2 t2;
	t2.std();
	t2.self();
	t2.binary();

	return 0;
}
