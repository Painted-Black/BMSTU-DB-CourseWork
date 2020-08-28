#pragma once

#include <QWidget>

#include "types/user_data.h"

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
	void setAccessData(const AccessData& acc_data);
	bool show(const QUrl& url, std::chrono::milliseconds tout, const QByteArray& pass);
signals:
	void new_visit();
private:
	QByteArray serializeCurrentDate();

private:
	Ui::MainTabWidget *ui;
	AccessData access_data;
};

