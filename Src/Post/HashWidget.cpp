//
// Created by 董文杰 on 2024-02-29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_HashWidget.h" resolved

#include "../Headers/HashWidget.h"
#include "../Forms/ui_HashWidget.h"
#include "../Algorithm/hashAlgorithm.cpp"
#include <QFileDialog>

HashWidget::HashWidget(QWidget* parent) : QWidget(parent), ui(new Ui::HashWidget) {
	ui->setupUi(this);

	connect(ui->inputFilePushButton, &QPushButton::clicked, this, &HashWidget::pushInputFileButton);
	connect(ui->outputPathPushButton, &QPushButton::clicked, this, &HashWidget::pushOutputFolderButton);
	connect(ui->commiPushButton, &QPushButton::clicked, this, &HashWidget::pushCommitButton);
	connect(ui->cancelPushButton, &QPushButton::clicked, this, &HashWidget::pushCancelButton);
}

HashWidget::~HashWidget() {
	delete ui;
}

void HashWidget::pushInputFileButton() {
	inputFilePath = QFileDialog::getOpenFileName(
			this,
			tr("choose file"),
			QDir::currentPath(),
			tr("c files(*.c);;other files(*.cpp *.txt);;All files(*.*)")
	);

	// 显示路径
	if (!inputFilePath.isEmpty()) {
		ui->showInputFileLabel->setText(inputFilePath);
	}
}

void HashWidget::pushOutputFolderButton() {
	outputFolderPath = QFileDialog::getExistingDirectory(
			this,
			tr("choose folder"),
			QDir::currentPath(),
			QFileDialog::ShowDirsOnly
	);

	// 显示路径
	if (!outputFolderPath.isEmpty()) {
		ui->showOutputFolderLabel->setText(outputFolderPath);
	}
}

void HashWidget::pushCommitButton() {
	// 异常处理
	if (inputFilePath.isEmpty() || outputFolderPath.isEmpty()) {

	}

	// funAlgo
	hashAlgorithm obj(inputFilePath.toStdString(), outputFolderPath.toStdString());
	int selfHashCnt = obj.selfHash();
	int binaryCnt = obj.binaryHash();

	// show data
	ui->hashResultLabel->setText(QString::number(selfHashCnt));
	ui->biniaryResultLabel->setText(QString::number(binaryCnt));
}

void HashWidget::pushCancelButton() {
	ui->showInputFileLabel->clear();
	ui->showOutputFolderLabel->clear();
	ui->hashResultLabel->clear();
	ui->biniaryResultLabel->clear();
}
