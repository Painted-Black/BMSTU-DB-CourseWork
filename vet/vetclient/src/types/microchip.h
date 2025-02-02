#ifndef MICROCHIP_H
#define MICROCHIP_H

#include <QString>
#include <QDate>
#include "QJsonHeaders.h"

#include "core/iserializable.h"

class Microchip final : public ISerializable<QJsonObject>
{
public:
	bool deserialize(const QJsonObject &json) noexcept override;
	QJsonObject serialize() const override;
	void setId(uint64_t);
	uint64_t getId() const;

	QString getChipNum() const;
	QDate getImplDate() const;
	QString getCountry() const;
	QString getLocation() const;

	void setChipNum(const QString &value);
	void setImplDate(const QDate &value);
	void setCountry(const QString &value);
	void setLocation(const QString &value);

	bool operator==(const Microchip&) const;
private:
	uint64_t id;
	QString chip_num;
	QDate impl_date;
	QString country;
	QString location;
};

#endif // MICROCHIP_H
