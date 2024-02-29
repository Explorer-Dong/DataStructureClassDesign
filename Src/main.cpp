#include <QApplication>
#include "Headers/SortWidget.h"
#include "Headers/HashWidget.h"
#include "Test/TestHash.cpp"

void Test2() {
	test2 t2;
	t2.std();
	t2.self();
	t2.binary();
}

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
//	SortWidget w;
	HashWidget h;
//	w.show();
	h.show();
	return app.exec();
}
