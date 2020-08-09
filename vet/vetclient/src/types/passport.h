#pragma once

#include <QDate>

#include "core/ISerializable.h"

class Gender : public ISerializable
{
public:
	enum class GenderEnum
	{
		Male,
		Female,
		Other
	};
public:
	bool deserialize(const QByteArray &) noexcept override;
	QByteArray serialize() const override;

	GenderEnum getGenderType() const;
	void setGenderType(GenderEnum value);

private:
	GenderEnum current;
};

class Passport : public ISerializable
{
public:
	bool deserialize(const QByteArray &) noexcept override;
	QByteArray serialize() const override;
	uint64_t getId() const;

	QString getSurname() const;
	void setSurname(const QString &value);

	QString getName() const;
	void setName(const QString &value);

	QString getPatronymic() const;
	void setPatronymic(const QString &value);

	QDate getBirthday() const;
	void setBirthday(const QDate &value);

	QDate getIssue_date() const;
	void setIssue_date(const QDate &value);

	QString getNationality() const;
	void setNationality(const QString &value);

	QString getPassport_num() const;
	void setPassport_num(const QString &value);

	Gender getGender() const;
	void setGender(const Gender &value);

private:
	uint64_t id;
	QString surname;
	QString name;
	QString patronymic;
	QDate birthday;
	QDate issue_date;
	QString nationality;
	QString passport_num;
	Gender gender;
};
