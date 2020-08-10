#ifndef MICROCHIP_H
#define MICROCHIP_H

#include <QString>
#include <QDate>
#include "QJsonHeaders.h"

#include "core/ISerializable.h"

class Microchip final : public ISerializable<QJsonObject>
{
public:
    bool deserialize(const QJsonObject &json) noexcept override;
    QJsonObject serialize() const override;
    uint64_t getId() const;

    QString getChip_num() const;
    QDate getImpl_date() const;
    QString getCountry() const;
    QString getLocation() const;

    void setChip_num(const QString &value);
    void setImpl_date(const QDate &value);
    void setCountry(const QString &value);
    void setLocation(const QString &value);
private:
    uint64_t id;
    QString chip_num;
    QDate impl_date;
    QString country;
    QString location;
};

#endif // MICROCHIP_H