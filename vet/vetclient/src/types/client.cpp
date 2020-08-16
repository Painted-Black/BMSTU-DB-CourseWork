#include <QVariant>
#include "client.h"
#include "json_fields.h"

bool Client::deserialize(const QJsonObject &json) noexcept
{
	bool ok = true;
	id = json.value(ClientJson::field_cli_id).toVariant().toULongLong(&ok);
	ok &= passport.deserialize(json.value(ClientJson::field_cli_passport).toObject());
	ok &= address.deserialize(json.value(ClientJson::field_cli_address).toObject());

	QJsonObject contacts = json.value(ClientJson::field_cli_contacts).toObject();
	QJsonArray phones_json = contacts.value(ClientJson::field_cli_phone).toArray();
	for (const auto& v : phones_json)
	{
		phones.push_back(v.toString());
	}

	QJsonArray email_json = contacts.value(ClientJson::field_cli_email).toArray();
	for (const auto& v : email_json)
	{
		emails.push_back(v.toString());
	}

	QJsonArray social_json = contacts.value(ClientJson::field_cli_social).toArray();
	for (const auto& v : social_json)
	{
		social.push_back(v.toString());
	}

	return ok;
}

QJsonObject Client::serialize() const
{
	QJsonObject root;
	root.insert(ClientJson::field_cli_id, QJsonValue::fromVariant(QVariant::fromValue(id)));
	root.insert(ClientJson::field_cli_passport, passport.serialize());
	root.insert(ClientJson::field_cli_address, address.serialize());

	QJsonObject contacts_json;

	QJsonArray phones_json;
	for (const auto& v : phones) { phones_json.push_back(v); }
	contacts_json.insert(ClientJson::field_cli_phone, phones_json);

	QJsonArray email_json;
	for (const auto& v : emails) { email_json.push_back(v); }
	contacts_json.insert(ClientJson::field_cli_email, email_json);

	QJsonArray social_json;
	for (const auto& v : social) { social_json.push_back(v.toString()); }
	contacts_json.insert(ClientJson::field_cli_social, social_json);

	root.insert(ClientJson::field_cli_contacts, contacts_json);
	return root;
}

uint64_t Client::getId() const
{
	return id;
}

Passport Client::getPassport() const
{
	return passport;
}

void Client::setPassport(const Passport &value)
{
	passport = value;
}

Address Client::getAddress() const
{
	return address;
}

void Client::setAddress(const Address &value)
{
	address = value;
}

QStringList Client::getPhones() const
{
	return phones;
}

void Client::setPhones(const QStringList &value)
{
	phones = value;
}

QStringList Client::getEmails() const
{
	return emails;
}

void Client::setEmails(const QStringList &value)
{
	emails = value;
}

QList<QUrl> Client::getSocial() const
{
	return social;
}

void Client::setSocial(const QList<QUrl> &value)
{
	social = value;
}
