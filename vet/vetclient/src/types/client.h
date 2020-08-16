#pragma once

#include <QString>
#include <QUrl>
#include "QJsonHeaders.h"

#include "core/ISerializable.h"
#include "passport.h"
#include "address.h"

class Client final : public ISerializable<QJsonObject>
{
public:
	bool deserialize(const QJsonObject &) noexcept override;
	QJsonObject serialize() const override;

	uint64_t getId() const;
	Passport getPassport() const;
	Address getAddress() const;
	QStringList getPhones() const;
	QStringList getEmails() const;
	QList<QUrl> getSocial() const;

	void setPassport(const Passport &value);
	void setAddress(const Address &value);
	void setPhones(const QStringList &value);
	void setEmails(const QStringList &value);
	void setSocial(const QList<QUrl> &value);

private:
	uint64_t id;
	Passport passport;
	Address address;
	QStringList phones;
	QStringList emails;
	QList<QUrl> social;
};
