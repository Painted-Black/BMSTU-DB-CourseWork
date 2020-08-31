#include <QVariant>

#include "user_data.h"
#include "json_fields.h"

bool AccessLevel::deserialize(const QJsonValue & v) noexcept
{
	QString value = v.toString();
	bool is_ok = false;
	if (value == AccessLevelType::access_vet)
	{
		current = AccessLevelEnum::Vet;
		is_ok = true;
	}
	else if (value == AccessLevelType::access_main)
	{
		current = AccessLevelEnum::Main;
		is_ok = true;
	}
	else if (value == AccessLevelType::access_admin)
	{
		current = AccessLevelEnum::Admin;
		is_ok = true;
	}
	else if (value == AccessLevelType::access_registry)
	{
		current = AccessLevelEnum::Registry;
		is_ok = true;
	}

	return is_ok;
}

QJsonValue AccessLevel::serialize() const
{
	QJsonValue value;
	switch (current)
	{
		case AccessLevelEnum::Vet:
			value = QJsonValue(AccessLevelType::access_vet);
			break;
		case AccessLevelEnum::Main:
			value = QJsonValue(AccessLevelType::access_main);
			break;
		case AccessLevelEnum::Admin:
			value = QJsonValue(AccessLevelType::access_admin);
			break;
		case AccessLevelEnum::Registry:
			value = QJsonValue(AccessLevelType::access_registry);
			break;
	}

	return value;
}

QString AccessLevel::toString()
{
	QString value;
	switch (current)
	{
		case AccessLevelEnum::Vet:
			value = AccessLevelType::access_vet;
			break;
		case AccessLevelEnum::Main:
			value = AccessLevelType::access_main;
			break;
		case AccessLevelEnum::Admin:
			value = AccessLevelType::access_admin;
			break;
		case AccessLevelEnum::Registry:
			value = AccessLevelType::access_registry;
			break;
	}
	return value;
}

bool AccessLevel::fromString(QString lvl)
{
	AccessLevelEnum level;
	bool is_ok = false;
	if (lvl == AccessLevelType::access_main)
	{
		level = AccessLevelEnum::Main;
		is_ok = true;
	}
	else if (lvl == AccessLevelType::access_vet)
	{
		level = AccessLevelEnum::Vet;
		is_ok = true;
	}
	else if (lvl == AccessLevelType::access_admin)
	{
		level = AccessLevelEnum::Admin;
		is_ok = true;
	}
	else if (lvl == AccessLevelType::access_registry)
	{
		level = AccessLevelEnum::Registry;
		is_ok = true;
	}
	if (is_ok == true)
	{
		current = level;
	}
	return is_ok;
}

bool AccessData::deserialize(const QJsonObject &document) noexcept
{
	bool ok = true;
	uid = document.value(AccessJson::field_acc_id).toVariant().toULongLong(&ok);
	login = document.value(AccessJson::field_acc_login).toString();
	password = document.value(AccessJson::field_acc_password).toVariant().toByteArray();
	ok &= employee.deserialize(document.value(AccessJson::field_acc_employee).toObject());
	ok &= level.deserialize(document.value(AccessJson::field_acc_access_level));
	return ok;
}

QJsonObject AccessData::serialize() const
{
	QJsonObject root;
	root.insert(AccessJson::field_acc_id, QJsonValue::fromVariant(QVariant::fromValue(uid)));
	root.insert(AccessJson::field_acc_employee, employee.serialize());
	root.insert(AccessJson::field_acc_login, login);
	root.insert(AccessJson::field_acc_password, QJsonValue::fromVariant(password));
	root.insert(AccessJson::field_acc_access_level, level.serialize());
	return root;
}

QString AccessData::getLogin() const
{
	return login;
}

void AccessData::setLogin(const QString &value)
{
	login = value;
}

uint64_t AccessData::getUid() const
{
	return uid;
}

QByteArray AccessData::getPassword() const
{
	return password;
}

void AccessData::setPassword(const QByteArray &value)
{
	password = value;
}

AccessLevel AccessData::getLevel() const
{
	return level;
}

void AccessData::setLevel(const AccessLevel &value)
{
	level = value;
}

const Staff& AccessData::getOwner() const
{
	return employee;
}

void AccessData::setOwner(const Staff &value)
{
	employee = value;
}
