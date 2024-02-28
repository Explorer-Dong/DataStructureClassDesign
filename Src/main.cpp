#include <QApplication>
#include "Headers/SortWidget.h"
#include "Algorithm/hashAlgorithm.cpp"
#include <unordered_map>

void test2std() {
	hashAlgorithm a;
	std::unordered_map<std::string, int> ha =  a.stdHash();

	for (const auto& pair : ha) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}
}

void test2self() {
	hashAlgorithm a;
	std::unordered_map<std::string, int> ha =  a.selfHash();

	for (const auto& pair : ha) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}
}

void test2binary() {
	hashAlgorithm a;
	std::unordered_map<std::string, int> ha =  a.binaryHash();

	for (const auto& pair : ha) {
		std::cout << pair.first << ": " << pair.second << std::endl;
	}
}

int main(int argc, char* argv[]) {
//	QApplication app(argc, argv);
//	SortWidget w;
//	w.show();
//	return app.exec();

	test2();
	return 0;
}
