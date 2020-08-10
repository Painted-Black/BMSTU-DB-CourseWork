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
    bool ok = true;

    const QJsonObject& document = QJsonDocument::fromJson(data).object();
    uid = document.value("acc_id").toVariant().toULongLong(&ok);
    login = document.value("login").toString();
    password = document.value("password").toVariant().toByteArray();
    ok &= owner.deserialize(document.value("employee").toObject());
    ok &= level.deserialize(document.value("access_level").toObject());
    return ok;
}

QByteArray AccessData::serialize() const
{
    QJsonObject root;
    root.insert("acc_id", QJsonValue::fromVariant(QVariant::fromValue(uid)));
    root.insert("employee", owner.serialize());
    root.insert("login", login);
    root.insert("password", QJsonValue::fromVariant(password));
    root.insert("access_level", level.serialize());
    return QJsonDocument(root).toJson();
}
