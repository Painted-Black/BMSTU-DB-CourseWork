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
	void init();
private:
	void update();
	void tableViewDoubleClicked(const QModelIndex &index);
	void addStaffBtn();
	void removeStaffBtn();
	bool fireQueryToServer(Staff fired_staff);
	void checked();
	bool getPositionsList(QVector<Position> *positions);

	Ui::StaffTabWidget *ui;
	QByteArray mPassword;
	StaffTableModel* model;
};

