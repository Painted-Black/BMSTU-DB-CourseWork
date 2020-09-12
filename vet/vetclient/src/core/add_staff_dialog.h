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
	enum Type
	{
		ADD,
		EDIT
	};

	explicit AddStaffDialog(Type type = ADD, QWidget *parent = nullptr);
	~AddStaffDialog();
	void setPassword(const QByteArray &password);
	void setPositionsList(const QVector<Position> &positionsList);
	void setEditableStaff(Staff staff);
	void readOnly();

private:
	void save_new();
	void addEduLevels();
	void update();
	void addSchedule();
	void deleteSchedule();
	bool insertStaffQueryToServer(const Staff& s);
	int findPositionIndex(QString title);
	int findEduIndex(QString edu);
	ScheduleList getSchedule(uint64_t staff_id);
	QJsonObject serializeId(uint64_t staff_id);
	bool updatePassportQuery(const Passport& new_pass);
	bool updateScheduleQuery(const ScheduleList& new_list, uint64_t staff_id);
	bool updateStaffQuery(const Staff& new_staff);
	QByteArray deserializeSchedule(const ScheduleList& new_list, uint64_t staff_id);
	QByteArray deserializeStaff(const Staff& s);

	Ui::AddStaffDialog *ui;
	Ui::PassportWidget *passport_w;
	QByteArray mPassword;
	QVector<Position> mPositionsList;
	StaffScheduleTableModel* model;
	Type mType;
	Staff mEditable;
};

