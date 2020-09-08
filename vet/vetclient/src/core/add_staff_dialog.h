#pragma once

#include <QDialog>

#include "types/position.h"
#include "types/schedule.h"
#include "model/staff_schedule_tablemodel.h"
#include "types/staff.h"

namespace Ui {
class AddStaffDialog;
class PassportWidget;
}

class AddStaffDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AddStaffDialog(QWidget *parent = nullptr);
	~AddStaffDialog();
	void setPassword(const QByteArray &password);
	void setPositionsList(const QVector<Position> &positionsList);

private:
	void accept() override;
	void addSchedule();
	void deleteSchedule();
	bool insertStaffQueryToServer(const Staff& s);

	Ui::AddStaffDialog *ui;
	Ui::PassportWidget *passport_w;
	QByteArray mPassword;
	QVector<Position> mPositionsList;
	StaffScheduleTableModel* model;
};

