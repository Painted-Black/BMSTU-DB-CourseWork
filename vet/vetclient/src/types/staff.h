#pragma once

#include "core/ISerializable.h"
#include "passport.h"
#include "position.h"

class EducationLevel : public ISerializable
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
	bool deserialize(const QByteArray &) noexcept override;
	QByteArray serialize() const override;

	EducationLevelEnum getEducationLevel() const;
	void setEducationLevel(const EducationLevelEnum &value);

private:
	EducationLevelEnum current;
};

class Staff : public ISerializable
{
public:
	bool deserialize(const QByteArray &) noexcept override;
	QByteArray serialize() const override;

	uint64_t getId() const;
	Passport getPassport() const;
	Position getPosition() const;
	EducationLevel getEdu_level() const;
	QDate getFire_date() const;
	QDate getEmploy_date() const;

	void setPassport(const Passport &value);
	void setPosition(const Position &value);
	void setEdu_level(const EducationLevel &value);
	void setFire_date(const QDate &value);
	void setEmploy_date(const QDate &value);

private:
	uint64_t id;
	Passport passport;
	Position position;
	EducationLevel edu_level;
	QDate fire_date;
	QDate employ_date;
};
