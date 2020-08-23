#pragma once

#include <QByteArray>
#include "types/QJsonHeaders.h"

QByteArray toJson(const QJsonObject&) noexcept;

QJsonObject fromJson(const QByteArray&) noexcept;
QJsonArray fromJsonArray(const QByteArray&) noexcept;

template<typename Class>
QVector<Class> deserializeArray(const QByteArray& data)
{
	QJsonArray arr = QJsonDocument::fromJson(data).array();
	QVector<Class> data_arr(arr.size());
	uint32_t idx = 0;
	for (QJsonValue a : arr)
	{
		data_arr[idx++].deserialize(a.toObject());
	}

	return data_arr;
}

