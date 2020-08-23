#include <QVariant>
#include <QDebug>

#include "microchip.h"
#include "json_fields.h"

bool Microchip::deserialize(const QJsonObject &json) noexcept
{
	bool cast = true;
	id = json.value(MicrochipJson::field_chip_id).toVariant().toULongLong(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << MicrochipJson::field_chip_id << "' field";
		return false;
	}
	chip_num = json.value(MicrochipJson::field_chip_chip_num).toString();
	impl_date = QDate::fromString(json.value(MicrochipJson::field_chip_impl_date).toString(), Qt::ISODate);
	if (impl_date.isValid() == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << MicrochipJson::field_chip_impl_date << "' field";
		return false;
	}
	country = json.value(MicrochipJson::field_chip_country).toString();
	location = json.value(MicrochipJson::field_chip_location).toString();
	return true;
}

QJsonObject Microchip::serialize() const
{
	QJsonObject root_obj;
	root_obj.insert(MicrochipJson::field_chip_id, QJsonValue::fromVariant(QVariant::fromValue(id)));
	root_obj.insert(MicrochipJson::field_chip_chip_num, QJsonValue(chip_num));
	root_obj.insert(MicrochipJson::field_chip_impl_date, QJsonValue(impl_date.toString(Qt::ISODate)));
	root_obj.insert(MicrochipJson::field_chip_country, QJsonValue(country));
	root_obj.insert(MicrochipJson::field_chip_location, QJsonValue(location));
	return root_obj;
}

uint64_t Microchip::getId() const
{
	return id;
}

QString Microchip::getChipNum() const
{
	return chip_num;
}

void Microchip::setChip_num(const QString &value)
{
	chip_num = value;
}

QDate Microchip::getImplDate() const
{
	return impl_date;
}

void Microchip::setImpl_date(const QDate &value)
{
	impl_date = value;
}

QString Microchip::getCountry() const
{
	return country;
}

void Microchip::setCountry(const QString &value)
{
	country = value;
}

QString Microchip::getLocation() const
{
	return location;
}

void Microchip::setLocation(const QString &value)
{
	location = value;
}
