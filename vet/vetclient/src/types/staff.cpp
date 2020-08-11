#include <QVariant>
#include <QDebug>

#include "staff.h"

bool EducationLevel::deserialize(const QJsonValue & json) noexcept
{
	QString data = json.toString();
	bool is_ok = false;
	if (data == "resident")
	{
		current = EducationLevelEnum::Resident;
		is_ok = true;
	}
	else if (data == "middle")
	{
		current = EducationLevelEnum::Middle;
		is_ok = true;
	}
	else if (data == "postgraduate")
	{
		current = EducationLevelEnum::Postgraduate;
		is_ok = true;
	}
	else if (data == "specialist")
	{
		current = EducationLevelEnum::Specialist;
		is_ok = true;
	}
	else if (data == "bachelor")
	{
		current = EducationLevelEnum::Bachelor;
		is_ok = true;
	}

	return is_ok;
}

QJsonValue EducationLevel::serialize() const
{
	QJsonValue value;
	switch (current)
	{
		case EducationLevelEnum::Resident:
			value = "resident";
			break;
		case EducationLevelEnum::Middle:
			value = "middle";
			break;
		case EducationLevelEnum::Postgraduate:
			value = "postgraduate";
			break;
		case EducationLevelEnum::Specialist:
			value = "specialist";
			break;
		case EducationLevelEnum::Bachelor:
			value = "bachelor";
			break;
	}

    return value;
}

EducationLevel::EducationLevelEnum EducationLevel::getEducationLevel() const
{
	return current;
}

void EducationLevel::setEducationLevel(const EducationLevelEnum &value)
{
	current = value;
}

bool Staff::deserialize(const QJsonObject & json) noexcept
{
	bool cast = true;
	id = json.value("staff_id").toVariant().toULongLong(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast 'staff_id' field";
		return false;
	}

	cast = passport.deserialize(json.value("passport").toObject());
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast 'passport' field";
		return false;
	}

	cast = position.deserialize(json.value("position").toObject());
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast 'position' field";
		return false;
	}

	cast = edu_level.deserialize(json.value("edu_level"));
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast 'edu_level' field";
		return false;
	}

	/* May be invalid */
	fire_date = QDate::fromString(json.value("fire_date").toString(), Qt::ISODate);

	employ_date = QDate::fromString(json.value("employ_date").toString(), Qt::ISODate);
	if (employ_date.isValid() == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast 'employ_date' field";
		return false;
	}

	return true;
}

QJsonObject Staff::serialize() const
{
	QJsonObject passport_json = passport.serialize();
	QJsonObject position_json = position.serialize();

	QJsonObject root_obj;
	root_obj.insert("staff_id", QJsonValue::fromVariant(QVariant::fromValue(id)));
	root_obj.insert("passport", passport_json);
	root_obj.insert("position", position_json);
	root_obj.insert("edu_level", QVariant(edu_level.serialize()).toJsonValue());
	root_obj.insert("fire_date", QJsonValue(fire_date.toString(Qt::ISODate)));
	root_obj.insert("employ_date", QJsonValue(employ_date.toString(Qt::ISODate)));
	return root_obj;
}

uint64_t Staff::getId() const
{
	return id;
}

Passport Staff::getPassport() const
{
	return passport;
}

void Staff::setPassport(const Passport &value)
{
	passport = value;
}

Position Staff::getPosition() const
{
	return position;
}

void Staff::setPosition(const Position &value)
{
	position = value;
}

EducationLevel Staff::getEdu_level() const
{
	return edu_level;
}

void Staff::setEdu_level(const EducationLevel &value)
{
	edu_level = value;
}

QDate Staff::getFire_date() const
{
	return fire_date;
}

void Staff::setFire_date(const QDate &value)
{
	fire_date = value;
}

QDate Staff::getEmploy_date() const
{
	return employ_date;
}

void Staff::setEmploy_date(const QDate &value)
{
	employ_date = value;
}
