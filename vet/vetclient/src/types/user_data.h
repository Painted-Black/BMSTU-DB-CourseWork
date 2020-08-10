#pragma once

#pragma once

#include <QString>
#include "QJsonHeaders.h"
#include "core/ISerializable.h"

class AccessLevel : public ISerializable<QJsonValue>
{
public:
	enum class AccessLevelEnum
	{
		Admin,
		Main,
		Registry,
		Vet
	};

	virtual bool deserialize(const QJsonValue &value) noexcept override;
	virtual QJsonValue serialize() const override;

private:
	AccessLevelEnum current;
};

class Staff
{

};

class AccessData : public ISerializable<QByteArray>
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
