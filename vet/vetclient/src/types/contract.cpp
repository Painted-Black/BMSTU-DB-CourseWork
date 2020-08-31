#include <QVariant>
#include <QDebug>

#include "contract.h"
#include "json_fields.h"

bool Contract::deserialize(const QJsonObject &json) noexcept
{
	bool cast = true;
	contr_id = json.value(ContractJson::field_contr_id).toVariant().toULongLong(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << ContractJson::field_contr_id << "' field";
	}

	code = json.value(ContractJson::field_contr_code).toString();

	conclusion_date = QDate::fromString(json.value(ContractJson::field_contr_conclusion_date).toString(), Qt::ISODate);
	if (conclusion_date.isValid() == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << ContractJson::field_contr_conclusion_date << "' field";
	}

	last_update_date = QDate::fromString(json.value(ContractJson::field_contr_last_update_date).toString(), Qt::ISODate);
	if (last_update_date.isValid() == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << ContractJson::field_contr_last_update_date << "' field";
	}

	valid_until = QDate::fromString(json.value(ContractJson::field_contr_valid_until).toString(), Qt::ISODate);
	if (valid_until.isValid() == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << ContractJson::field_contr_valid_until << "' field";
	}

	cast = client.deserialize(json.value(ContractJson::field_contr_owner).toObject());
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << ContractJson::field_contr_owner << "' field";
	}
	return true;
}

QJsonObject Contract::serialize() const
{
	QJsonObject root_obj;
	QJsonObject owner_json = client.serialize();

	root_obj.insert(ContractJson::field_contr_id, QJsonValue::fromVariant(QVariant::fromValue(contr_id)));
	root_obj.insert(ContractJson::field_contr_conclusion_date, QJsonValue(conclusion_date.toString(Qt::ISODate)));
	root_obj.insert(ContractJson::field_contr_last_update_date, QJsonValue(last_update_date.toString(Qt::ISODate)));
	root_obj.insert(ContractJson::field_contr_valid_until, QJsonValue(valid_until.toString(Qt::ISODate)));
	root_obj.insert(ContractJson::field_contr_owner, owner_json);
	root_obj.insert(ContractJson::field_contr_code, QJsonValue(code));
	return root_obj;
}

uint64_t Contract::getContrId() const
{
	return contr_id;
}

QDate Contract::getConclusionDate() const
{
	return conclusion_date;
}

void Contract::setConclusionDate(const QDate &value)
{
	conclusion_date = value;
}

QDate Contract::getLastUpdateDate() const
{
	return last_update_date;
}

void Contract::setLastUpdateDate(const QDate &value)
{
	last_update_date = value;
}

QDate Contract::getValidUntil() const
{
	return valid_until;
}

void Contract::setValidUntil(const QDate &value)
{
	valid_until = value;
}

const Client& Contract::getClient() const
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

bool Contract::operator==(const Contract & v) const
{
	bool is_equal = true;
	is_equal &= (code == v.code);
	is_equal &= (conclusion_date == v.conclusion_date);
	is_equal &= (last_update_date == v.last_update_date);
	is_equal &= (valid_until == v.valid_until);
	is_equal &= (client == v.client);
	return is_equal;
}
