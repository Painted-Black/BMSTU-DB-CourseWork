#pragma once

#include <QDate>

#include "QJsonHeaders.h"
#include "core/iserializable.h"
#include "gender.h"

class Passport : public ISerializable<QJsonObject>
{
public:
	bool deserialize(const QJsonObject&) noexcept override;
	QJsonObject serialize() const override;

	void setSurname(const QString &value);
	void setName(const QString &value);
	void setPatronymic(const QString &value);
	void setBirthday(const QDate &value);
	void setIssueDate(const QDate &value);
	void setNationality(const QString &value);
	void setPassportNum(const QString &value);
	void setGender(const Gender &value);

	uint64_t getId() const;
	const QString& getSurname() const;
	const QString& getName() const;
	const QString& getPatronymic() const;
	const QDate& getBirthday() const;
	const QDate& getIssueDate() const;
	const QString& getNationality() const;
	const QString& getPassportNum() const;
	Gender getGender() const;

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
