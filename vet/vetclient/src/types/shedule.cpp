#include <QVariant>
#include <QDebug>

#include "shedule.h"

bool DayOfWeek::deserialize(const QJsonValue &json) noexcept
{
    QString v = json.toString();
    bool is_ok = false;
    if (v == "Sun")
    {
        current = DayOfWeekEnum::Sun;
        is_ok = true;
    }
    else if (v == "Mon")
    {
        current = DayOfWeekEnum::Mon;
        is_ok = true;
    }
    else if (v == "Tue")
    {
        current = DayOfWeekEnum::Tue;
        is_ok = true;
    }
    else if (v == "Wed")
    {
        current = DayOfWeekEnum::Wed;
        is_ok = true;
    }
    else if (v == "Thu")
    {
        current = DayOfWeekEnum::Thu;
        is_ok = true;
    }
    else if (v == "Fri")
    {
        current = DayOfWeekEnum::Fri;
        is_ok = true;
    }
    else if (v == "Sat")
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
            value = "Sun";
            break;
        case DayOfWeekEnum::Mon:
            value = "Mon";
            break;
        case DayOfWeekEnum::Tue:
            value = "Tue";
            break;
        case DayOfWeekEnum::Wed:
            value = "Wed";
            break;
        case DayOfWeekEnum::Thu:
            value = "Thu";
            break;
        case DayOfWeekEnum::Fri:
            value = "Fri";
            break;
        case DayOfWeekEnum::Sat:
            value = "Sat";
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
    shed_id = json.value("shed_id").toVariant().toULongLong(&cast);
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'shed_id' field";
        return false;
    }

    cast = empoyee.deserialize(json.value("employee_id").toObject());
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast 'employee_id' field";
        return false;
    }

    cast = day_of_week.deserialize(json.value("day_of_week"));
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast 'day_of_week' field";
        return false;
    }

    type = json.value("type").toString();

    start = QDateTime::fromString(json.value("start").toString(), Qt::ISODate);
    end = QDateTime::fromString(json.value("end").toString(), Qt::ISODate);

    cabinet = json.value("cabinet").toString();
    return true;
}

QJsonObject Shedule::serialize() const
{
    QJsonObject root_obj;
    root_obj.insert("staff_id", QJsonValue::fromVariant(QVariant::fromValue(shed_id)));
    root_obj.insert("employee_id", QVariant(empoyee.serialize()).toJsonValue());
    root_obj.insert("day_of_week", QVariant(day_of_week.serialize()).toJsonValue());
    root_obj.insert("type", QJsonValue(type));
    root_obj.insert("start", QJsonValue(start.toString(Qt::ISODate)));
    root_obj.insert("end", QJsonValue(end.toString(Qt::ISODate)));
    root_obj.insert("cabinet", QJsonValue(cabinet));
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
