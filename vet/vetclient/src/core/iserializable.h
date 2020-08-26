#pragma once

#include <QByteArray>
#include <QDebug>

template <typename T>
struct ISerializable
{
	virtual ~ISerializable() noexcept = default;
	virtual T serialize() const { qFatal("Use undefined function"); }
	virtual bool deserialize(const T&) noexcept { qFatal("Use undefined function"); }
};
