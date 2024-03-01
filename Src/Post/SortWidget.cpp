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
	QString dataNumber = ui->countLineEdit->text();

	// 异常处理
	if (dataNumber.isEmpty()) {
		return;
	}
	bool ok;
	dataNumber.toInt(&ok);
	if (!ok) { return; }

	if (dataNumber.toInt() > 1e8 || dataNumber.toInt() < 0) {
		return;
	}

	int scale = dataNumber.toInt();


	sortAlgorithm obj(scale, 1000, path.toStdString());
	ui->shellResultLabel->setText(QString::number(obj.ShellSort()));
	ui->heapResultLabel->setText(QString::number(obj.HeapSort()));
	ui->quickResultLabel->setText(QString::number(obj.QuickSort()));
	ui->mergeResultLabel->setText(QString::number(obj.MergeSort()));
}

void SortWidget::pushCancelButton() {
	ui->countLineEdit->clear();
	ui->shellResultLabel->clear();
	ui->heapResultLabel->clear();
	ui->quickResultLabel->clear();
	ui->mergeResultLabel->clear();
}
