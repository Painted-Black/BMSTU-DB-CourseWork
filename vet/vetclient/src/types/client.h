#pragma once

#include <QString>
#include <QUrl>
#include "QJsonHeaders.h"

#include "core/ISerializable.h"
#include "passport.h"
#include "address.h"

class Client final : public ISerializable<QJsonObject>
{
public:
    bool deserialize(const QJsonObject &) noexcept override;
    QJsonObject serialize() const override;
private:
    uint64_t id;
    Passport passport;
    Address address;
    QStringList phones;
    QStringList emails;
    QList<QUrl> social;
};
