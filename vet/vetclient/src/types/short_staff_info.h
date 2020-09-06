#pragma once

#include <QDate>
#include "types/QJsonHeaders.h"
#include "core/iserializable.h"
#include "user_data.h"

class ShortStaffInfo : public ISerializable<QJsonObject>
{
public:
	virtual QJsonObject serialize() const override;
	virtual bool deserialize(const QJsonObject &json) noexcept override;
	uint64_t getUid() const;
	void setUid(const uint64_t &value);

	QString getName() const;
	void setName(const QString &value);

	QString getSurname() const;
	void setSurname(const QString &value);

	QString getPatr() const;
	void setPatr(const QString &value);

	QString getFio() const;
	void setFio(const QString &value);

	QString getPosition() const;
	void setPosition(const QString &value);

	QDate getEmpl() const;
	void setEmpl(const QDate &value);

	QDate getFire() const;
	void setFire(const QDate &value);

private:
	uint64_t uid;
	QString name;
	QString surname;
	QString patr;
	QString fio;
	QString position;
	QDate empl;
	QDate fire;
};

