//
// Created by 董文杰 on 2024-02-28.
//

#ifndef DATASTRUCTURECLASSDESIGN_SORTWIDGET_H
#define DATASTRUCTURECLASSDESIGN_SORTWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
	class SortWidget;
}
QT_END_NAMESPACE

class SortWidget : public QWidget {
Q_OBJECT

private:
	Ui::SortWidget* ui;
	QString path;

private slots:
	void pushFolderButton();
	void pushCommitButton();
	void pushCancelButton();

public:
	explicit SortWidget(QWidget* parent = nullptr);

	~SortWidget() override;
};


#endif //DATASTRUCTURECLASSDESIGN_SORTWIDGET_H
