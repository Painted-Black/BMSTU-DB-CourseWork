#include <QJsonObject>
#include <QVariant>
#include "proxy_auth.h"

std::tuple<Staff, AccessData, Passport, QByteArray> ProxyAuth::deserialize(const QByteArray& json)
{
    QJsonObject root = QJsonDocument::fromJson(json).array().first().toObject();
    Staff staff;
    staff.deserialize(root);

    Passport passport;
    passport.deserialize(root);

    AccessData data;
    data.deserialize(root);

    QByteArray key = root.value("key").toVariant().toByteArray();

    return decltype (ProxyAuth::deserialize(json))(staff, data, passport, key);
}
