#pragma once

#include <QWidget>

namespace Ui {
class MainTabWidget;
}

class MainTabWidget : public QWidget
{
	Q_OBJECT

public:
	explicit MainTabWidget(QWidget *parent = nullptr);
	~MainTabWidget();
	void new_visit_btn_pressed();
signals:
	void new_visit();

private:
	Ui::MainTabWidget *ui;
};

