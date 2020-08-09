#pragma once

#pragma once

#include <QString>
#include "core/ISerializable.h"

class AccessLevel : public ISerializable
{
public:
	enum class AccessLevelEnum
	{
		Admin,
		Main,
		Registry,
		Vet
	};

	virtual bool deserialize(const QByteArray &value) noexcept override;
	virtual QByteArray serialize() const override;

private:
	AccessLevelEnum current;
};

class Staff
{

};

class AccessData : public ISerializable
{
public:
	virtual bool deserialize(const QByteArray &) noexcept override;
	virtual QByteArray serialize() const override;

private:
	uint64_t uid;
	QString login;
	QByteArray password;
	AccessLevel level;
};
