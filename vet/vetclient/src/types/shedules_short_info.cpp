#include "shedules_short_info.h"
#include "types/json_fields.h"

QJsonObject ShedulesShortInfo::serialize() const
{
	QJsonObject root_obj;

//	root_obj.insert()
//	unused
	return root_obj;
}

bool ShedulesShortInfo::deserialize(const QJsonObject &json) noexcept
{
	bool is_ok = true;
	QJsonObject staff_obj = json.value("staff").toObject();
	mStaffId = staff_obj.value(StaffJson::field_staff_id).toVariant().value<uint64_t>();
	QJsonObject position_obj = staff_obj.value(StaffJson::field_staff_position).toObject();
	QJsonObject passport_obj = staff_obj.value(StaffJson::field_staff_passport).toObject();
	QJsonArray schedule_arr = json.value("schedule").toArray();

	mPassId = passport_obj.value(PassportJson::field_pass_id).toVariant().value<uint64_t>();
	mSurname = passport_obj.value(PassportJson::field_pass_surname).toString();
	mName = passport_obj.value(PassportJson::field_pass_name).toString();
	mPatr = passport_obj.value(PassportJson::field_pass_patronymic).toString();

	mPosId = position_obj.value(PositionJson::field_pos_id).toVariant().value<uint64_t>();
	mPosTitle = position_obj.value(PositionJson::field_pos_title).toString();
	is_ok = mSchedList.deserialize(schedule_arr);
	if (is_ok == false)
	{
		qDebug() << "Failed to deserialize Schedule List";
		return false;
	}

	mFio = mSurname;
	if (mName.size() >= 1)
	{
		mFio += " ";
		mFio += mName.at(0);
		mFio += ".";
	}
	if (mPatr.size() >= 1)
	{
		mFio += " ";
		mFio += mPatr.at(0);
		mFio += ".";
	}
	return true;
}

ScheduleList ShedulesShortInfo::schedList() const
{
	return mSchedList;
}

void ShedulesShortInfo::setSchedList(const ScheduleList &schedList)
{
	mSchedList = schedList;
}

uint64_t ShedulesShortInfo::staffId() const
{
	return mStaffId;
}

void ShedulesShortInfo::setStaffId(const uint64_t &staffId)
{
	mStaffId = staffId;
}

uint64_t ShedulesShortInfo::posId() const
{
	return mPosId;
}

void ShedulesShortInfo::setPosId(const uint64_t &posId)
{
	mPosId = posId;
}

uint64_t ShedulesShortInfo::passId() const
{
	return mPassId;
}

void ShedulesShortInfo::setPassId(const uint64_t &passId)
{
	mPassId = passId;
}

QString ShedulesShortInfo::posTitle() const
{
	return mPosTitle;
}

void ShedulesShortInfo::setPosTitle(const QString &posTitle)
{
	mPosTitle = posTitle;
}

QString ShedulesShortInfo::surname() const
{
	return mSurname;
}

void ShedulesShortInfo::setSurname(const QString &surname)
{
	mSurname = surname;
}

QString ShedulesShortInfo::name() const
{
	return mName;
}

void ShedulesShortInfo::setName(const QString &name)
{
	mName = name;
}

QString ShedulesShortInfo::patr() const
{
	return mPatr;
}

void ShedulesShortInfo::setPatr(const QString &patr)
{
	mPatr = patr;
}

QString ShedulesShortInfo::fio() const
{
	return mFio;
}

void ShedulesShortInfo::setFio(const QString &fio)
{
	mFio = fio;
}
