#pragma once

#include <QString>
#include <QDate>
#include "QJsonHeaders.h"

#include "core/ISerializable.h"
#include "types/client.h"

class Contract final : public ISerializable<QJsonObject>
{
public:
	bool deserialize(const QJsonObject &json) noexcept override;
	QJsonObject serialize() const override;

	uint64_t getContr_id() const;
	QDate getConclusion_date() const;
	QDate getLast_update_date() const;
	QDate getValid_until() const;
	Client getClient() const;
	QString getCode() const;

	void setConclusion_date(const QDate &value);
	void setLast_update_date(const QDate &value);
	void setValid_until(const QDate &value);
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

