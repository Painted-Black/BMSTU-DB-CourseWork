#pragma once

#include <QByteArray>

template <typename T>
struct ISerializable
{
	virtual ~ISerializable() noexcept = default;
	virtual T serialize() const = 0;
	virtual bool deserialize(const T&) noexcept = 0;
};
