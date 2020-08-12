#include <QVariant>
#include <QDebug>

#include "staff.h"
#include "json_fields.h"

bool EducationLevel::deserialize(const QJsonValue & json) noexcept
{
	QString data = json.toString();
	bool is_ok = false;
    if (data == EduLevelType::edu_resident)
	{
		current = EducationLevelEnum::Resident;
		is_ok = true;
	}
    else if (data == EduLevelType::edu_middle)
	{
		current = EducationLevelEnum::Middle;
		is_ok = true;
	}
    else if (data == EduLevelType::edu_postgraduate)
	{
		current = EducationLevelEnum::Postgraduate;
		is_ok = true;
	}
    else if (data == EduLevelType::edu_specialist)
	{
		current = EducationLevelEnum::Specialist;
		is_ok = true;
	}
    else if (data == EduLevelType::edu_bachelor)
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
            value = EduLevelType::edu_resident;
			break;
		case EducationLevelEnum::Middle:
            value = EduLevelType::edu_middle;
			break;
		case EducationLevelEnum::Postgraduate:
            value = EduLevelType::edu_postgraduate;
			break;
		case EducationLevelEnum::Specialist:
            value = EduLevelType::edu_specialist;
			break;
		case EducationLevelEnum::Bachelor:
            value = EduLevelType::edu_bachelor;
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
    id = json.value(StaffJson::field_staff_id).toVariant().toULongLong(&cast);
	if (cast == false)
	{
        qCritical() << Q_FUNC_INFO << "Invalid cast '" << StaffJson::field_staff_id << "' field";
		return false;
	}

    cast = passport.deserialize(json.value(StaffJson::field_staff_passport).toObject());
	if (cast == false)
	{
        qCritical() << Q_FUNC_INFO << "invalid cast '" << StaffJson::field_staff_passport << "' field";
		return false;
	}

    cast = position.deserialize(json.value(StaffJson::field_staff_position).toObject());
	if (cast == false)
	{
        qCritical() << Q_FUNC_INFO << "invalid cast '" << StaffJson::field_staff_position << "' field";
		return false;
	}

    cast = edu_level.deserialize(json.value(StaffJson::field_staff_edu_level));
	if (cast == false)
	{
        qCritical() << Q_FUNC_INFO << "invalid cast '" << StaffJson::field_staff_edu_level << "' field";
		return false;
	}

	/* May be invalid */
    fire_date = QDate::fromString(json.value(StaffJson::field_staff_fire_date).toString(), Qt::ISODate);

    employ_date = QDate::fromString(json.value(StaffJson::field_staff_employ_date).toString(), Qt::ISODate);
	if (employ_date.isValid() == false)
	{
        qCritical() << Q_FUNC_INFO << "invalid cast '" << StaffJson::field_staff_employ_date << "' field";
		return false;
	}

	return true;
}

QJsonObject Staff::serialize() const
{
	QJsonObject passport_json = passport.serialize();
	QJsonObject position_json = position.serialize();

	QJsonObject root_obj;
    root_obj.insert(StaffJson::field_staff_id, QJsonValue::fromVariant(QVariant::fromValue(id)));
    root_obj.insert(StaffJson::field_staff_passport, passport_json);
    root_obj.insert(StaffJson::field_staff_position, position_json);
    root_obj.insert(StaffJson::field_staff_edu_level, edu_level.serialize());
    root_obj.insert(StaffJson::field_staff_fire_date, QJsonValue(fire_date.toString(Qt::ISODate)));
    root_obj.insert(StaffJson::field_staff_employ_date, QJsonValue(employ_date.toString(Qt::ISODate)));
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
