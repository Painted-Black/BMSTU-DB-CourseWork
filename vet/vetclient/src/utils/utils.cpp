#include <QJsonDocument>
#include "utils.h"

QByteArray toJson(const QJsonObject & obj) noexcept
{
	return QJsonDocument(obj).toJson();
}


QJsonObject fromJson(const QByteArray & json) noexcept
{
	return QJsonDocument::fromJson(json).object();
}

QJsonArray fromJsonArray(const QByteArray & json) noexcept
{
	return QJsonDocument::fromJson(json).array();
}
