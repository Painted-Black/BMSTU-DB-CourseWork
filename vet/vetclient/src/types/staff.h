#pragma once

#include <QString>

#include "QJsonHeaders.h"
#include "core/iserializable.h"
#include "passport.h"
#include "position.h"
#include "types/schedule.h"

class EducationLevel : public ISerializable<QJsonValue>
{
public:
	enum class EducationLevelEnum
	{
		Resident,
		Middle,
		Postgraduate,
		Specialist,
		Bachelor
	};
public:
	bool deserialize(const QJsonValue&) noexcept override;
	QJsonValue serialize() const override;
	bool operator==(const EducationLevel& edu);
	bool operator!=(const EducationLevel& edu);

	EducationLevelEnum getEducationLevel() const;
	void setEducationLevel(const EducationLevelEnum &value);

	QString toString();
	QString toEngString();
	bool fromString(const QString& lvl);

private:
	EducationLevelEnum current;
};

class Staff : public ISerializable<QJsonObject>
{
public:
	bool deserialize(const QJsonObject&) noexcept override;
	QJsonObject serialize() const override;

	uint64_t getId() const;
	const Passport &getPassport() const;
	Position getPosition() const;
	EducationLevel getEdu_level() const;
	QDate getFire_date() const;
	QDate getEmploy_date() const;
	ScheduleList getShed_list() const;
	QVector<Schedule> toVector() const;

	void setPassport(const Passport &value);
	void setPosition(const Position &value);
	void setEdu_level(const EducationLevel &value);
	void setFire_date(const QDate &value);
	void setEmploy_date(const QDate &value);
	void setShed_list(const ScheduleList &value);
	void setId(const uint64_t &value);

private:
	uint64_t id;
	Passport passport;
	Position position;
	EducationLevel edu_level;
	QDate fire_date;
	QDate employ_date;
	ScheduleList shed_list;
};
