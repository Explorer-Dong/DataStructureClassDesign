//
// Created by 董文杰 on 2024-02-29.
//

#ifndef DATASTRUCTURECLASSDESIGN_HASHWIDGET_H
#define DATASTRUCTURECLASSDESIGN_HASHWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
	class HashWidget;
}
QT_END_NAMESPACE

class HashWidget : public QWidget {
Q_OBJECT

private:
	Ui::HashWidget* ui;
	QString inputFilePath, outputFolderPath;

private slots:
	void pushInputFileButton();
	void pushOutputFolderButton();
	void pushCommitButton();
	void pushCancelButton();

public:
	explicit HashWidget(QWidget* parent = nullptr);

	~HashWidget() override;

};


#endif //DATASTRUCTURECLASSDESIGN_HASHWIDGET_H
