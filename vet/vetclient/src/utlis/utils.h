#pragma once

#include <QByteArray>
#include <QJsonObject>

QByteArray toJson(const QJsonObject&) noexcept;
QJsonObject fromJson(const QByteArray&) noexcept;

