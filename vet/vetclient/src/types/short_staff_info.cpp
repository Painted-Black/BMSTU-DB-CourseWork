#include "short_staff_info.h"
#include "json_fields.h"
#include "types/staff.h"
#include "types/position.h"
#include "types/passport.h"

QJsonObject ShortStaffInfo::serialize() const
{
	QJsonObject root_obj;

//	root_obj.insert()
//	unused
	return root_obj;
}

bool ShortStaffInfo::deserialize(const QJsonObject &json) noexcept
{
	bool is_ok = true;
	uid = json.value(AccessJson::field_acc_id).toVariant().value<uint64_t>();
	QJsonObject passport_json = json.value(StaffJson::field_staff_passport).toObject();
	QJsonObject position_json = json.value(StaffJson::field_staff_position).toObject();
	empl = QDate::fromString(json.value(StaffJson::field_staff_employ_date).toString());
	fire = QDate::fromString(json.value(StaffJson::field_staff_fire_date).toString());
	name = passport_json.value(PassportJson::field_pass_name).toString();
	surname = passport_json.value(PassportJson::field_pass_surname).toString();
	patr = passport_json.value(PassportJson::field_pass_patronymic).toString();
	position = position_json.value(PositionJson::field_pos_title).toString();

	fio = surname;
	if (name.size() >= 0)
	{
		fio += " ";
		fio += name[0];
		fio += ".";
	}
	if (patr.size() >= 0)
	{
		fio += " ";
		fio += patr[0];
		fio += ".";
	}
	return is_ok;
}

uint64_t ShortStaffInfo::getUid() const
{
    return uid;
}

void ShortStaffInfo::setUid(const uint64_t &value)
{
    uid = value;
}

QString ShortStaffInfo::getName() const
{
    return name;
}

void ShortStaffInfo::setName(const QString &value)
{
    name = value;
}

QString ShortStaffInfo::getSurname() const
{
    return surname;
}

void ShortStaffInfo::setSurname(const QString &value)
{
    surname = value;
}

QString ShortStaffInfo::getPatr() const
{
    return patr;
}

void ShortStaffInfo::setPatr(const QString &value)
{
    patr = value;
}

QString ShortStaffInfo::getFio() const
{
    return fio;
}

void ShortStaffInfo::setFio(const QString &value)
{
    fio = value;
}

QString ShortStaffInfo::getPosition() const
{
    return position;
}

void ShortStaffInfo::setPosition(const QString &value)
{
    position = value;
}

QDate ShortStaffInfo::getEmpl() const
{
    return empl;
}

void ShortStaffInfo::setEmpl(const QDate &value)
{
    empl = value;
}

QDate ShortStaffInfo::getFire() const
{
    return fire;
}

void ShortStaffInfo::setFire(const QDate &value)
{
    fire = value;
}
