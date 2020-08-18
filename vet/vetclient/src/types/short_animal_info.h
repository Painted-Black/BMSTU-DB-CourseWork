#pragma once

#include <QDate>
#include "types/QJsonHeaders.h"
#include "core/ISerializable.h"

class ShortAnimalInfo : public ISerializable<QJsonObject>
{
public:
	virtual QJsonObject serialize() const override;
	virtual bool deserialize(const QJsonObject &) noexcept override;

	uint64_t getUid() const;
	const QString& getName() const;
	const QString& getSpec() const;
	const QDate& getBirth() const;

	void setUid(uint64_t);
	void setName(const QString &value);
	void setSpec(const QString &value);
	void setBirth(const QDate &value);

private:
	uint64_t uid;
	QString name;
	QString spec;
	QDate birth;
};

