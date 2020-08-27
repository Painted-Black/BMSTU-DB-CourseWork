#include <QVariant>
#include <QDebug>

#include "schedule.h"
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

QString DayOfWeek::toString()
{
	QString value;
	switch (current)
	{
		case DayOfWeekEnum::Sun:
			value = RussianDayOfWeekType::rus_day_of_week_sun;
			break;
		case DayOfWeekEnum::Mon:
			value = RussianDayOfWeekType::rus_day_of_week_mon;
			break;
		case DayOfWeekEnum::Tue:
			value = RussianDayOfWeekType::rus_day_of_week_tue;
			break;
		case DayOfWeekEnum::Wed:
			value = RussianDayOfWeekType::rus_day_of_week_wed;
			break;
		case DayOfWeekEnum::Thu:
			value = RussianDayOfWeekType::rus_day_of_week_thu;
			break;
		case DayOfWeekEnum::Fri:
			value = RussianDayOfWeekType::rus_day_of_week_fri;
			break;
		case DayOfWeekEnum::Sat:
			value = RussianDayOfWeekType::rus_day_of_week_fri;
			break;
	}
	return value;
}

bool Schedule::deserialize(const QJsonObject &json) noexcept
{
	bool cast = true;
	shed_id = json.value(ScheduleJson::field_shed_id).toVariant().toULongLong(&cast);
	cast &= day_of_week.deserialize(json.value(ScheduleJson::field_shed_day_of_week));
	cabinet = json.value(ScheduleJson::field_shed_cabinet).toString();
	start = QTime::fromString(json.value(ScheduleJson::field_shed_start).toString(), Qt::ISODate);
	end = QTime::fromString(json.value(ScheduleJson::field_shed_end).toString(), Qt::ISODate);
	cast &= start.isValid();
	cast &= end.isValid();

	return true;
}

QJsonObject Schedule::serialize() const
{
	QJsonObject root_obj;
	root_obj.insert(ScheduleJson::field_shed_id, QJsonValue::fromVariant(QVariant::fromValue(shed_id)));
	root_obj.insert(ScheduleJson::field_shed_day_of_week, QVariant(day_of_week.serialize()).toJsonValue());
	root_obj.insert(ScheduleJson::field_shed_start, QJsonValue(start.toString(Qt::ISODate)));
	root_obj.insert(ScheduleJson::field_shed_end, QJsonValue(end.toString(Qt::ISODate)));
	root_obj.insert(ScheduleJson::field_shed_cabinet, QJsonValue(cabinet));
	return root_obj;
}

uint64_t Schedule::getShed_id() const
{
	return shed_id;
}

DayOfWeek Schedule::getDay_of_week() const
{
	return day_of_week;
}

void Schedule::setDay_of_week(const DayOfWeek &value)
{
	day_of_week = value;
}

QTime Schedule::getStart() const
{
	return start;
}

void Schedule::setStart(const QTime &value)
{
	start = value;
}

QTime Schedule::getEnd() const
{
	return end;
}

void Schedule::setEnd(const QTime &value)
{
	end = value;
}

QString Schedule::getCabinet() const
{
	return cabinet;
}

void Schedule::setCabinet(const QString &value)
{
	cabinet = value;
}

bool ScheduleList::deserialize(const QJsonArray &jarray) noexcept
{
	bool is_ok = true;

	for (const QJsonValue& val : jarray)
	{
		Schedule shed;
		is_ok &= shed.deserialize(val.toObject());
		add_shedule_item(shed);
	}
	return is_ok;
}

QJsonArray ScheduleList::serialize() const
{
	QJsonArray result;

	for (const Schedule& s : shedule_list)
	{
		const QJsonValue& val = s.serialize();
		result.push_back(val);
	}

	return result;
}

void ScheduleList::add_shedule_item(Schedule &shed)
{
	shedule_list.push_back(shed);
}

const Schedule& ScheduleList::at(int idx) const
{
	return shedule_list.at(idx);
}

int ScheduleList::size() const
{
	return shedule_list.size();
}

QVector<Schedule> ScheduleList::getShedule_list() const
{
	return shedule_list;
}
