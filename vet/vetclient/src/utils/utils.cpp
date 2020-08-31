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

QMap<QString, QString> fromSimpleJson(const QByteArray &json) noexcept
{
	QMap<QString, QString> out;
	QJsonObject json_obj = fromJson(json);
	QStringList keys = json_obj.keys();
	for (const QString& key : keys)
	{
		out[key] = json_obj[key].toString();
	}
	return out;
}
