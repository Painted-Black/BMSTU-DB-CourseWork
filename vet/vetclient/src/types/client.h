#pragma once

#include <QString>
#include <QUrl>
#include "QJsonHeaders.h"

#include "core/iserializable.h"
#include "passport.h"
#include "address.h"

class Client final : public ISerializable<QJsonObject>
{
public:
	bool deserialize(const QJsonObject &) noexcept override;
	QJsonObject serialize() const override;

	uint64_t getId() const;
	const Passport& getPassport() const;
	const Address& getAddress() const;
	const QStringList& getPhones() const;
	const QStringList& getEmails() const;
	const QList<QUrl>& getSocial() const;

	void setPhones(const QStringList &value);
	void setEmails(const QStringList &value);
	void setSocial(const QList<QUrl> &value);

	template<typename T>
	void setAddress(T&& value)
	{
		address = std::forward<Address>(value);
	}

	template<typename T>
	void setPassport(T&& value)
	{
		passport = std::forward<Passport>(value);
	}

	bool operator ==(const Client&) const;

private:
	uint64_t id;
	Passport passport;
	Address address;
	QStringList phones;
	QStringList emails;
	QList<QUrl> social;
};
