#pragma once

#include <memory>
#include <QByteArray>

struct ISerializable
{
	virtual ~ISerializable() noexcept = default;
	virtual QByteArray serialize() const = 0;
	virtual bool deserialize(const QByteArray&) noexcept = 0;
};
