#include <QJsonObject>
#include <QVariant>
#include "proxy_auth.h"

std::tuple<AccessData, QByteArray> ProxyAuth::deserialize(const QByteArray& json)
{
    QJsonObject root = QJsonDocument::fromJson(json).object();

    AccessData data;
    data.deserialize(root);

    QByteArray key = root.value("key").toVariant().toByteArray();

    return { data, key };
}
