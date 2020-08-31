#pragma once

#include "types/QJsonHeaders.h"
#include "core/iserializable.h"

#include <QDate>

class SheduledVisits : public ISerializable<QJsonObject>
{
public:
	virtual QJsonObject serialize() const override;
	virtual bool deserialize(const QJsonObject &json) noexcept override;

	QDate getDate() const;
	void setDate(const QDate &value);

	QString getAnimalName() const;
	void setAnimalName(const QString &value);

	QString getAnimalSpecies() const;
	void setAnimalSpecies(const QString &value);

private:
	QDate date;
	QString animal_name;
	QString animal_species;
};

