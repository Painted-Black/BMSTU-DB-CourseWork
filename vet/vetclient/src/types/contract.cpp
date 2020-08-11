#include <QVariant>
#include <QDebug>

#include "contract.h"

bool Contract::deserialize(const QJsonObject &json) noexcept
{
    bool cast = true;
    contr_id = json.value("contr_id").toVariant().toULongLong(&cast);
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'contr_id' field";
        return false;
    }

    code = json.value("code").toString();

    conclusion_date = QDate::fromString(json.value("conclusion_date").toString(), Qt::ISODate);
    if (conclusion_date.isValid() == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast 'conclusion_date' field";
        return false;
    }

    last_update_date = QDate::fromString(json.value("last_update_date").toString(), Qt::ISODate);
    if (last_update_date.isValid() == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast 'last_update_date' field";
        return false;
    }

    valid_until = QDate::fromString(json.value("valid_until").toString(), Qt::ISODate);
    if (valid_until.isValid() == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast 'valid_until' field";
        return false;
    }

    cast = client.deserialize(json.value("owner").toObject());
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast 'owner' field";
        return false;
    }
    return true;
}

QJsonObject Contract::serialize() const
{
    QJsonObject root_obj;
    QJsonObject owner_json = client.serialize();

    root_obj.insert("contr_id", QJsonValue::fromVariant(QVariant::fromValue(contr_id)));
    root_obj.insert("conclusion_date", QJsonValue(conclusion_date.toString(Qt::ISODate)));
    root_obj.insert("last_update_date", QJsonValue(last_update_date.toString(Qt::ISODate)));
    root_obj.insert("valid_until", QJsonValue(valid_until.toString(Qt::ISODate)));
    root_obj.insert("owner", owner_json);
    root_obj.insert("code", QJsonValue(code));
    return root_obj;
}

uint64_t Contract::getContr_id() const
{
    return contr_id;
}

QDate Contract::getConclusion_date() const
{
    return conclusion_date;
}

void Contract::setConclusion_date(const QDate &value)
{
    conclusion_date = value;
}

QDate Contract::getLast_update_date() const
{
    return last_update_date;
}

void Contract::setLast_update_date(const QDate &value)
{
    last_update_date = value;
}

QDate Contract::getValid_until() const
{
    return valid_until;
}

void Contract::setValid_until(const QDate &value)
{
    valid_until = value;
}

Client Contract::getClient() const
{
    return client;
}

void Contract::setClient(const Client &value)
{
    client = value;
}

QString Contract::getCode() const
{
    return code;
}

void Contract::setCode(const QString &value)
{
    code = value;
}
