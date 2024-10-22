#pragma once

#include "QJsonHeaders.h"
#include "core/iserializable.h"
#include "types/staff.h"

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
	QString toString();
	bool fromString(QString lvl);
	bool isAdmin() const;
	bool isMain() const;
	bool isRegistry() const;
	bool isVet() const;

private:
	AccessLevelEnum current;
};

class AccessData final : public ISerializable<QJsonObject>
{
public:
	virtual bool deserialize(const QJsonObject &) noexcept override;
	virtual QJsonObject serialize() const override;

	QString getLogin() const;
	uint64_t getUid() const;
	QByteArray getPassword() const;
	AccessLevel getLevel() const;
	const Staff &getOwner() const;
	void setLogin(const QString &value);
	void setPassword(const QByteArray &value);
	void setLevel(const AccessLevel &value);
	void setOwner(const Staff &value);

private:
	uint64_t uid;
	QString login;
	QByteArray password;
	AccessLevel level;
	Staff employee;
};
