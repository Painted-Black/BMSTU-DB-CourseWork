#pragma once

#include <QDate>
#include "types/QJsonHeaders.h"
#include "core/iserializable.h"
#include "user_data.h"

class ShortUserInfo : public ISerializable<QJsonObject>
{
public:
	virtual QJsonObject serialize() const override;
	virtual bool deserialize(const QJsonObject &json) noexcept override;
	uint64_t getUid() const;

	QString getLogin() const;
	void setLogin(const QString &value);

	QString getSurname() const;
	void setSurname(const QString &value);

	QString getName() const;
	void setName(const QString &value);

	QString getPatronymic() const;
	void setPatronymic(const QString &value);

	QString getAccessLevel() const;
	void setAccessLevel(const QString &value);

	QString getPositionTitle() const;
	void setPositionTitle(const QString &value);

	QDate getEmployDate() const;
	void setEmployDate(const QDate &value);

	QDate getFireDate() const;
	void setFireDate(const QDate &value);

	QString getFio() const;
	void setFio(const QString &value);

	AccessLevel getAccessLevelType() const;
	void setAccessLevelType(const AccessLevel &value);

private:
	uint64_t uid;
	QString login;
	QString surname;
	QString name;
	QString patronymic;
	QString access_level;
	QString position_title;
	QDate employed;
	QDate fired;

	QString fio;
	AccessLevel acc_level;
};

