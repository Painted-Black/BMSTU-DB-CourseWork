#include <QVariant>
#include <QDebug>

#include "passport.h"
#include "json_fields.h"

bool Passport::deserialize(const QJsonObject &obj) noexcept
{
	bool cast = true;
	id = obj.value(PassportJson::field_pass_id).toVariant().toULongLong(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << PassportJson::field_pass_id << "' field";
		return false;
	}

	surname = obj.value(PassportJson::field_pass_surname).toString();
	name = obj.value(PassportJson::field_pass_name).toString();
	patronymic = obj.value(PassportJson::field_pass_patronymic).toString();

	if (gender.deserialize(obj.value(PassportJson::field_pass_sex)) == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << PassportJson::field_pass_sex << "' field";
		return false;
	}
	// 2020-12-20T12:40:40 (yyyy-mm-ddThh:MM:ss)
	birthday = QDate::fromString(obj.value(PassportJson::field_pass_birth).toString(), Qt::ISODate);
	if (birthday.isValid() == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << PassportJson::field_pass_birth << "' field";
		return false;
	}

	passport_num = obj.value(PassportJson::field_pass_num).toString();
	issue_date = QDate::fromString(obj.value(PassportJson::field_pass_issue_date).toString(), Qt::ISODate);
	if (issue_date.isValid() == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << PassportJson::field_pass_issue_date <<"' field";
		return false;
	}

	nationality = obj.value(PassportJson::field_pass_nationality).toString();
	return true;
}

QJsonObject Passport::serialize() const
{
	QJsonObject root_obj;
	root_obj.insert(PassportJson::field_pass_id, QJsonValue::fromVariant(QVariant::fromValue(id)));
	root_obj.insert(PassportJson::field_pass_surname, QJsonValue(surname));
	root_obj.insert(PassportJson::field_pass_name, QJsonValue(name));
	root_obj.insert(PassportJson::field_pass_patronymic, QJsonValue(patronymic));
	root_obj.insert(PassportJson::field_pass_sex, QVariant(gender.serialize()).toJsonValue());
	root_obj.insert(PassportJson::field_pass_birth, QJsonValue(birthday.toString(Qt::ISODate)));
	root_obj.insert(PassportJson::field_pass_issue_date, QJsonValue(issue_date.toString(Qt::ISODate)));
	root_obj.insert(PassportJson::field_pass_nationality, QJsonValue(nationality));
	root_obj.insert(PassportJson::field_pass_num, QJsonValue(QString(passport_num.data(),
											  static_cast<int>(passport_num.size()))));
	return root_obj;
}

uint64_t Passport::getId() const
{
	return id;
}

QString Passport::getSurname() const
{
	return surname;
}

void Passport::setSurname(const QString &value)
{
	surname = value;
}

QString Passport::getName() const
{
	return name;
}

void Passport::setName(const QString &value)
{
	name = value;
}

QString Passport::getPatronymic() const
{
	return patronymic;
}

void Passport::setPatronymic(const QString &value)
{
	patronymic = value;
}

QDate Passport::getBirthday() const
{
	return birthday;
}

void Passport::setBirthday(const QDate &value)
{
	birthday = value;
}

QDate Passport::getIssue_date() const
{
	return issue_date;
}

void Passport::setIssue_date(const QDate &value)
{
	issue_date = value;
}

QString Passport::getNationality() const
{
	return nationality;
}

void Passport::setNationality(const QString &value)
{
	nationality = value;
}

QString Passport::getPassport_num() const
{
	return passport_num;
}

void Passport::setPassport_num(const QString &value)
{
	passport_num = value;
}

Gender Passport::getGender() const
{
	return gender;
}

void Passport::setGender(const Gender &value)
{
	gender = value;
}
