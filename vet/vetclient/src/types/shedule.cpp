#include <QVariant>
#include <QDebug>

#include "shedule.h"
#include "json_fields.h"

bool DayOfWeek::deserialize(const QJsonValue &json) noexcept
{
    QString v = json.toString();
    bool is_ok = false;
    if (v == DayOfWeekType::day_of_week_sun)
    {
        current = DayOfWeekEnum::Sun;
        is_ok = true;
    }
    else if (v == DayOfWeekType::day_of_week_mon)
    {
        current = DayOfWeekEnum::Mon;
        is_ok = true;
    }
    else if (v == DayOfWeekType::day_of_week_tue)
    {
        current = DayOfWeekEnum::Tue;
        is_ok = true;
    }
    else if (v == DayOfWeekType::day_of_week_wed)
    {
        current = DayOfWeekEnum::Wed;
        is_ok = true;
    }
    else if (v == DayOfWeekType::day_of_week_thu)
    {
        current = DayOfWeekEnum::Thu;
        is_ok = true;
    }
    else if (v == DayOfWeekType::day_of_week_fri)
    {
        current = DayOfWeekEnum::Fri;
        is_ok = true;
    }
    else if (v == DayOfWeekType::day_of_week_sat)
    {
        current = DayOfWeekEnum::Sat;
        is_ok = true;
    }
    return is_ok;
}

QJsonValue DayOfWeek::serialize() const
{
    QJsonValue value;
    switch (current)
    {
        case DayOfWeekEnum::Sun:
            value = DayOfWeekType::day_of_week_sun;
            break;
        case DayOfWeekEnum::Mon:
            value = DayOfWeekType::day_of_week_mon;
            break;
        case DayOfWeekEnum::Tue:
            value = DayOfWeekType::day_of_week_tue;
            break;
        case DayOfWeekEnum::Wed:
            value = DayOfWeekType::day_of_week_wed;
            break;
        case DayOfWeekEnum::Thu:
            value = DayOfWeekType::day_of_week_thu;
            break;
        case DayOfWeekEnum::Fri:
            value = DayOfWeekType::day_of_week_fri;
            break;
        case DayOfWeekEnum::Sat:
            value = DayOfWeekType::day_of_week_fri;
            break;
    }
    return value;
}

DayOfWeek::DayOfWeekEnum DayOfWeek::getDayOfkWeek() const
{
    return current;
}

void DayOfWeek::setDayOfkWeek(DayOfWeek::DayOfWeekEnum value)
{
    current = value;
}

bool Shedule::deserialize(const QJsonObject &json) noexcept
{
    bool cast = true;
    shed_id = json.value(ScheduleJson::field_shed_id).toVariant().toULongLong(&cast);
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast '" << ScheduleJson::field_shed_id << "' field";
        return false;
    }

    cast = empoyee.deserialize(json.value(ScheduleJson::field_shed_employee_id).toObject());
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast '" << ScheduleJson::field_shed_employee_id << "' field";
        return false;
    }

    cast = day_of_week.deserialize(json.value(ScheduleJson::field_shed_day_of_week));
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast '" << ScheduleJson::field_shed_day_of_week << "' field";
        return false;
    }

    type = json.value(ScheduleJson::field_shed_type).toString();

    start = QDateTime::fromString(json.value(ScheduleJson::field_shed_start).toString(), Qt::ISODate);
    if (start.isValid() == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast '" << ScheduleJson::field_shed_start << "' field";
        return false;
    }

    end = QDateTime::fromString(json.value(ScheduleJson::field_shed_end).toString(), Qt::ISODate);
    if (end.isValid() == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast '" << ScheduleJson::field_shed_end << "' field";
        return false;
    }

    cabinet = json.value(ScheduleJson::field_shed_cabinet).toString();
    return true;
}

QJsonObject Shedule::serialize() const
{
    QJsonObject root_obj;
    root_obj.insert(ScheduleJson::field_shed_id, QJsonValue::fromVariant(QVariant::fromValue(shed_id)));
    root_obj.insert(ScheduleJson::field_shed_employee_id, QVariant(empoyee.serialize()).toJsonValue());
    root_obj.insert(ScheduleJson::field_shed_day_of_week, QVariant(day_of_week.serialize()).toJsonValue());
    root_obj.insert(ScheduleJson::field_shed_type, QJsonValue(type));
    root_obj.insert(ScheduleJson::field_shed_start, QJsonValue(start.toString(Qt::ISODate)));
    root_obj.insert(ScheduleJson::field_shed_end, QJsonValue(end.toString(Qt::ISODate)));
    root_obj.insert(ScheduleJson::field_shed_cabinet, QJsonValue(cabinet));
    return root_obj;
}

uint64_t Shedule::getShed_id() const
{
    return shed_id;
}

Staff Shedule::getEmpoyee() const
{
    return empoyee;
}

void Shedule::setEmpoyee(const Staff &value)
{
    empoyee = value;
}

DayOfWeek Shedule::getDay_of_week() const
{
    return day_of_week;
}

void Shedule::setDay_of_week(const DayOfWeek &value)
{
    day_of_week = value;
}

QString Shedule::getType() const
{
    return type;
}

void Shedule::setType(const QString &value)
{
    type = value;
}

QDateTime Shedule::getStart() const
{
    return start;
}

void Shedule::setStart(const QDateTime &value)
{
    start = value;
}

QDateTime Shedule::getEnd() const
{
    return end;
}

void Shedule::setEnd(const QDateTime &value)
{
    end = value;
}

QString Shedule::getCabinet() const
{
    return cabinet;
}

void Shedule::setCabinet(const QString &value)
{
    cabinet = value;
}
