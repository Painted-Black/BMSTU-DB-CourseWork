#pragma once

#include <QString>
#include "QJsonHeaders.h"

#include "core/iserializable.h"

class Address final : public ISerializable<QJsonObject>
{
public:
	bool deserialize(const QJsonObject &) noexcept override;
	QJsonObject serialize() const override;

	uint64_t getId() const;
	QString getCountry() const;
	QString getCity() const;
	QString getStreet() const;
	QString getHouse() const;
	QString getFlat() const;

	void setId(uint64_t value);
	void setCountry(const QString &value);
	void setCity(const QString &value);
	void setStreet(const QString &value);
	void setHouse(const QString &value);
	void setFlat(const QString &value);

	bool operator==(const Address&) const;


private:
	uint64_t id;
	QString country;
	QString city;
	QString street;
	QString house;
	QString flat;
};
