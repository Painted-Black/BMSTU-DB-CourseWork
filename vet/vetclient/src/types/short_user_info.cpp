#include "short_user_info.h"
#include "json_fields.h"


QJsonObject ShortUserInfo::serialize() const
{
	QJsonObject root_obj;

//	root_obj.insert()
//	unused
	return root_obj;
}

bool ShortUserInfo::deserialize(const QJsonObject &json) noexcept
{
	bool is_ok = true;
	uid = json.value(AccessJson::field_acc_id).toVariant().value<uint64_t>();
	login = json.value(AccessJson::field_acc_login).toString();

	QJsonObject user = json.value(AccessJson::field_acc_employee).toObject();
	QJsonObject passport = user.value(StaffJson::field_staff_passport).toObject();

	name = passport.value(PassportJson::field_pass_name).toString();
	surname = passport.value(PassportJson::field_pass_surname).toString();
	patronymic = passport.value(PassportJson::field_pass_patronymic).toString();
	password = json.value(AccessJson::field_acc_password).toVariant().toByteArray();

	fio = surname;
	if (name.size() >= 1)
	{
		fio += " ";
		fio += name.at(0);
		fio += ".";
	}
	if (patronymic.size() >= 1)
	{
		fio += " ";
		fio += patronymic.at(0);
		fio += ".";
	}
	access_level = json.value(AccessJson::field_acc_access_level).toString();
	is_ok = acc_level.fromString(access_level);

	QJsonObject position = user.value(StaffJson::field_staff_position).toObject();
	position_title = position.value(PositionJson::field_pos_title).toString();
	employed = QDate::fromString(user.value(StaffJson::field_staff_employ_date).toString(),
								 Qt::ISODate);
	fired = QDate::fromString(user.value(StaffJson::field_staff_fire_date).toString(),
							  Qt::ISODate);
	is_ok &= employed.isValid();
	return true;
}

uint64_t ShortUserInfo::getUid() const
{
	return uid;
}

QString ShortUserInfo::getLogin() const
{
	return login;
}

void ShortUserInfo::setLogin(const QString &value)
{
	login = value;
}

QString ShortUserInfo::getSurname() const
{
	return surname;
}

void ShortUserInfo::setSurname(const QString &value)
{
	surname = value;
}

QString ShortUserInfo::getName() const
{
	return name;
}

void ShortUserInfo::setName(const QString &value)
{
	name = value;
}

QString ShortUserInfo::getPatronymic() const
{
	return patronymic;
}

void ShortUserInfo::setPatronymic(const QString &value)
{
	patronymic = value;
}

QString ShortUserInfo::getFio() const
{
	return fio;
}

void ShortUserInfo::setFio(const QString &value)
{
	fio = value;
}

AccessLevel ShortUserInfo::getAccessLevelType() const
{
	return acc_level;
}

void ShortUserInfo::setAccessLevelType(const AccessLevel &value)
{
	acc_level = value;
}

QByteArray ShortUserInfo::getPassword() const
{
	return password;
}

void ShortUserInfo::setPassword(const QByteArray &value)
{
	password = value;
}

QDate ShortUserInfo::getFireDate() const
{
	return fired;
}

void ShortUserInfo::setFireDate(const QDate &value)
{
	fired = value;
}

QDate ShortUserInfo::getEmployDate() const
{
	return employed;
}

void ShortUserInfo::setEmployDate(const QDate &value)
{
	employed = value;
}

QString ShortUserInfo::getPositionTitle() const
{
	return position_title;
}

void ShortUserInfo::setPositionTitle(const QString &value)
{
	position_title = value;
}

QString ShortUserInfo::getAccessLevel() const
{
	return access_level;
}

void ShortUserInfo::setAccessLevel(const QString &value)
{
	access_level = value;
}
