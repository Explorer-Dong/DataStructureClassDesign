//
// Created by 董文杰 on 2024-02-28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SortWidget.h" resolved

#include "../Headers/SortWidget.h"
#include "../Forms/ui_SortWidget.h"
#include "../Algorithm/sortAlgorithm.cpp"


SortWidget::SortWidget(QWidget* parent) : QWidget(parent), ui(new Ui::SortWidget) {
	ui->setupUi(this);
	this->setWindowTitle("排序比较器");
	connect(ui->commitPushButton, &QPushButton::clicked, this, &SortWidget::pushCommitButton);
	connect(ui->cancelPushButton, &QPushButton::clicked, this, &SortWidget::pushCancelButton);
}

SortWidget::~SortWidget() {
	delete ui;
}

int SortWidget::getNumber() {
	QString dataNumber = ui->countLineEdit->text();

	// 异常处理

	return dataNumber.toInt();
}

vector<int> SortWidget::funAlgo() {
	int dataNumber = getNumber();
	sortAlgorithm obj(dataNumber);

	vector<int> result(4);

	int shellCount = obj.ShellSort();
	int heapCount = obj.HeapSort();
	int quickCount = obj.QuickSort();
	int mergeCount = obj.MergeSort();

	result[0] = shellCount;
	result[1] = heapCount;
	result[2] = quickCount;
	result[3] = mergeCount;

	return result;
}

void SortWidget::outputResult() {
	vector<int> result = funAlgo();

	int shellCount = result[0];
	int heapCount = result[1];
	int quickCount = result[2];
	int mergeCount = result[3];

	ui->shellLineEdit->setText(QString::number(shellCount));
	ui->heapLineEdit->setText(QString::number(heapCount));
	ui->quickLineEdit->setText(QString::number(quickCount));
	ui->mergeLineEdit->setText(QString::number(mergeCount));
}

void SortWidget::pushCommitButton() {
	outputResult();
}

void SortWidget::pushCancelButton() {
	ui->countLineEdit->clear();
	ui->shellLineEdit->clear();
	ui->heapLineEdit->clear();
	ui->quickLineEdit->clear();
	ui->mergeLineEdit->clear();
}
