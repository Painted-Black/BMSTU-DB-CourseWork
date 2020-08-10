#include <QVariant>
#include "user_data.h"

bool AccessLevel::deserialize(const QJsonValue & v) noexcept
{
	QString value = v.toString();
	bool is_ok = false;
	if (value == "vet")
	{
		current = AccessLevelEnum::Vet;
		is_ok = true;
	}
	else if (value == "main")
	{
		current = AccessLevelEnum::Main;
		is_ok = true;
	}
	else if (value == "admin")
	{
		current = AccessLevelEnum::Admin;
		is_ok = true;
	}
	else if (value == "registry")
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
			value = QJsonValue("vet");
			break;
		case AccessLevelEnum::Main:
			value = QJsonValue("main");
			break;
		case AccessLevelEnum::Admin:
			value = QJsonValue("admin");
			break;
		case AccessLevelEnum::Registry:
			value = QJsonValue("registry");
			break;
	}

	return value;
}

bool AccessData::deserialize(const QByteArray & data) noexcept
{

}

QByteArray AccessData::serialize() const
{

}
