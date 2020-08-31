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
	for (auto v : phones_json)
	{
		phones.push_back(v.toString());
	}

	QJsonArray email_json = contacts.value(ClientJson::field_cli_email).toArray();
	for (auto v : email_json)
	{
		emails.push_back(v.toString());
	}

	QJsonArray social_json = contacts.value(ClientJson::field_cli_social).toArray();
	for (auto v : social_json)
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

const Passport &Client::getPassport() const
{
	return passport;
}

const Address &Client::getAddress() const
{
	return address;
}

const QStringList &Client::getPhones() const
{
	return phones;
}

void Client::setPhones(const QStringList &value)
{
	phones = value;
}

const QStringList &Client::getEmails() const
{
	return emails;
}

void Client::setEmails(const QStringList &value)
{
	emails = value;
}

const QList<QUrl> &Client::getSocial() const
{
	return social;
}

void Client::setSocial(const QList<QUrl> &value)
{
	social = value;
}

bool Client::operator ==(const Client & v) const
{
	bool is_equal = true;
	is_equal &= (passport == v.passport);
	is_equal &= (address == v.address);
	is_equal &= (phones == v.phones);
	is_equal &= (emails == v.emails);
	is_equal &= (social == v.social);

	return is_equal;
}
