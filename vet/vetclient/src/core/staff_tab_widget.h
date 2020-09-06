#pragma once

#include <QWidget>

#include "model/staff_table_model.h"

namespace Ui {
class StaffTabWidget;
}

class StaffTabWidget : public QWidget
{
	Q_OBJECT

public:
	explicit StaffTabWidget(QWidget *parent = nullptr);
	~StaffTabWidget();

	void setPassword(const QByteArray &password);
	void update();

private:
	void addStaffBtn();
	void removeStaffBtn();

	Ui::StaffTabWidget *ui;
	QByteArray mPassword;
	StaffTableModel* model;
};
