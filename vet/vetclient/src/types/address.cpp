#include <QVariant>
#include <QDebug>

#include "address.h"
#include "json_fields.h"

bool Address::deserialize(const QJsonObject &obj) noexcept
{
    bool cast = true;
    id = obj.value(AddressJson::field_addr_id).toVariant().toULongLong(&cast);
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast  '" << AddressJson::field_addr_id <<"' field";
        return false;
    }
    country = obj.value(AddressJson::field_addr_country).toString();
    city = obj.value(AddressJson::field_addr_city).toString();
    street = obj.value(AddressJson::field_addr_street).toString();
    house = obj.value(AddressJson::field_addr_house).toString();
    flat = obj.value(AddressJson::field_addr_flat).toString();
    return true;
}

QJsonObject Address::serialize() const
{
    QJsonObject root_obj;
    root_obj.insert(AddressJson::field_addr_id, QJsonValue::fromVariant(QVariant::fromValue(id)));
    root_obj.insert(AddressJson::field_addr_country, QJsonValue(country));
    root_obj.insert(AddressJson::field_addr_city, QJsonValue(city));
    root_obj.insert(AddressJson::field_addr_street, QJsonValue(street));
    root_obj.insert(AddressJson::field_addr_house, QJsonValue(house));
    root_obj.insert(AddressJson::field_addr_flat, QJsonValue(flat));
    return root_obj;
}

uint64_t Address::getId() const
{
    return id;
}

QString Address::getCountry() const
{
    return country;
}

void Address::setCountry(const QString &value)
{
    country = value;
}

QString Address::getCity() const
{
    return city;
}

void Address::setCity(const QString &value)
{
    city = value;
}

QString Address::getStreet() const
{
    return street;
}

void Address::setStreet(const QString &value)
{
    street = value;
}

QString Address::getHouse() const
{
    return house;
}

void Address::setHouse(const QString &value)
{
    house = value;
}

QString Address::getFlat() const
{
    return flat;
}

void Address::setFlat(const QString &value)
{
    flat = value;
}
