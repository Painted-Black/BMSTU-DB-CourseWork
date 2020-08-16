#pragma once

#include <QString>
#include <QDateTime>
#include "QJsonHeaders.h"

#include "core/ISerializable.h"

class DayOfWeek : public ISerializable<QJsonValue>
{
public:
	enum class DayOfWeekEnum
	{
		Sun,
		Mon,
		Tue,
		Wed,
		Thu,
		Fri,
		Sat
	};
public:
	bool deserialize(const QJsonValue&json) noexcept override;
	QJsonValue serialize() const override;

	DayOfWeekEnum getDayOfkWeek() const;
	void setDayOfkWeek(DayOfWeekEnum value);

private:
	DayOfWeekEnum current;
};

class Schedule final : public ISerializable<QJsonObject>
{
public:
	bool deserialize(const QJsonObject &json) noexcept override;
	QJsonObject serialize() const override;

	uint64_t getShed_id() const;
	DayOfWeek getDay_of_week() const;
	QString getType() const;
	QTime getStart() const;
	QTime getEnd() const;
	QString getCabinet() const;

	void setDay_of_week(const DayOfWeek &value);
	void setType(const QString &value);
	void setStart(const QTime &value);
	void setEnd(const QTime &value);
	void setCabinet(const QString &value);

private:
	uint64_t shed_id;
	DayOfWeek day_of_week;
	QTime start;
	QTime end;
	QString cabinet;
};

class ScheduleList final : public ISerializable<QJsonArray>
{
public:
	bool deserialize(const QJsonArray &jarray) noexcept override;
	QJsonArray serialize() const override;
	void add_shedule_item(Schedule& shed);

	QList<Schedule> getShedule_list() const;

private:
	QList<Schedule> shedule_list;
};


