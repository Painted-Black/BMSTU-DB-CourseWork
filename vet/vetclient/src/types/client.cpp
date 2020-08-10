#include <QVariant>
#include "client.h"

bool Client::deserialize(const QJsonObject &json) noexcept
{
    bool ok = true;
    id = json.value("cli_id").toVariant().toULongLong(&ok);
    ok &= passport.deserialize(json.value("passport").toObject());
    ok &= address.deserialize(json.value("address").toObject());

    QJsonArray phones_json = json.value("phone").toArray();
    for (const auto& v : phones_json)
    {
        phones.push_back(v.toString());
    }

    QJsonArray email_json = json.value("email").toArray();
    for (const auto& v : email_json)
    {
        emails.push_back(v.toString());
    }

    QJsonArray social_json = json.value("social").toArray();
    for (const auto& v : social_json)
    {
        social.push_back(v.toString());
    }

    return ok;
}

QJsonObject Client::serialize() const
{
    QJsonObject root;
    root.insert("cli_id", QJsonValue::fromVariant(QVariant::fromValue(id)));
    root.insert("passport", passport.serialize());
    root.insert("address", address.serialize());

    QJsonObject contacts_json;

    QJsonArray phones_json;
    for (const auto& v : phones) { phones_json.push_back(v); }
    contacts_json.insert("phone", phones_json);

    QJsonArray email_json;
    for (const auto& v : emails) { email_json.push_back(v); }
    contacts_json.insert("email", email_json);

    QJsonArray social_json;
    for (const auto& v : social) { social_json.push_back(v.toString()); }
    contacts_json.insert("social", social_json);

    root.insert("contacts", contacts_json);
    return root;
}
