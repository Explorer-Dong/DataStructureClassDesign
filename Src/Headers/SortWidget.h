//
// Created by 董文杰 on 2024-02-28.
//

#ifndef DATASTRUCTURECLASSDESIGN_SORTWIDGET_H
#define DATASTRUCTURECLASSDESIGN_SORTWIDGET_H

#include <QWidget>
#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui {
	class SortWidget;
}
QT_END_NAMESPACE

class SortWidget : public QWidget {
Q_OBJECT

private:
	Ui::SortWidget* ui;

private slots:
	void pushCommitButton();
	void pushCancelButton();

public:
	explicit SortWidget(QWidget* parent = nullptr);

	// 算法
	int getNumber();
	std::vector<int> funAlgo();
	void outputResult();

	~SortWidget() override;
};


#endif //DATASTRUCTURECLASSDESIGN_SORTWIDGET_H
