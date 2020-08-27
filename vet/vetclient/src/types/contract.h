#pragma once

#include <QString>
#include <QDate>
#include "QJsonHeaders.h"

#include "core/iserializable.h"
#include "types/client.h"

class Contract final : public ISerializable<QJsonObject>
{
public:
	bool deserialize(const QJsonObject &json) noexcept override;
	QJsonObject serialize() const override;

	uint64_t getContrId() const;
	QDate getConclusionDate() const;
	QDate getLastUpdateDate() const;
	QDate getValidUntil() const;
	const Client &getClient() const;
	QString getCode() const;

	void setConclusionDate(const QDate &value);
	void setLastUpdateDate(const QDate &value);
	void setValidUntil(const QDate &value);
	void setClient(const Client &value);
	void setCode(const QString &value);

private:
	uint64_t contr_id;
	QString code;
	QDate conclusion_date;
	QDate last_update_date;
	QDate valid_until;
	Client client;
};

