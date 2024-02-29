//
// Created by 董文杰 on 2024-02-28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SortWidget.h" resolved

#include "../Headers/SortWidget.h"
#include "../Forms/ui_SortWidget.h"
#include "../Algorithm/sortAlgorithm.cpp"
#include <QFileDialog>


SortWidget::SortWidget(QWidget* parent) : QWidget(parent), ui(new Ui::SortWidget) {
	ui->setupUi(this);
	this->setWindowTitle("排序比较器");
	connect(ui->folderPushButton, &QPushButton::clicked, this, &SortWidget::pushFolderButton);
	connect(ui->commitPushButton, &QPushButton::clicked, this, &SortWidget::pushCommitButton);
	connect(ui->cancelPushButton, &QPushButton::clicked, this, &SortWidget::pushCancelButton);
}

SortWidget::~SortWidget() {
	delete ui;
}

void SortWidget::pushFolderButton() {
	path = QFileDialog::getExistingDirectory(
			this,
			tr("choose folder"),
			QDir::currentPath(),
			QFileDialog::ShowDirsOnly
	);

	// 异常处理
	if (path.isEmpty()) {
		return;
	}
	ui->pathLabel->setText(path);
}

void SortWidget::pushCommitButton() {
	int dataNumber = ui->countLineEdit->text().toInt();

	// 异常处理
	if (dataNumber < 0 || dataNumber >= 1e8) {
		return;
	}

	sortAlgorithm obj(dataNumber, 1000, path.toStdString());
	ui->shellLineEdit->setText(QString::number(obj.ShellSort()));
	ui->heapLineEdit->setText(QString::number(obj.HeapSort()));
	ui->quickLineEdit->setText(QString::number(obj.QuickSort()));
	ui->mergeLineEdit->setText(QString::number(obj.MergeSort()));
}

void SortWidget::pushCancelButton() {
	ui->countLineEdit->clear();
	ui->shellLineEdit->clear();
	ui->heapLineEdit->clear();
	ui->quickLineEdit->clear();
	ui->mergeLineEdit->clear();
}
