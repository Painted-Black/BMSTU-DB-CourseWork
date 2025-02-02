#pragma once

#include <QMap>

#include "QJsonHeaders.h"
#include "core/iserializable.h"

class InjectionType : public ISerializable<QJsonValue>
{
public:
	enum class InjectionTypeEnum
	{
		Subcutaneous,
		Intravenous,
		Intramuscular,
		Ingest
	};
	bool deserialize(const QJsonValue &json) noexcept override;
	QJsonValue serialize() const override;
	QString toString();
	InjectionTypeEnum getInjectionType() const;
	void setInjectionType(const InjectionTypeEnum &value);
	bool fromString(const QString& type);

private:
	InjectionTypeEnum current;
};

class Medicine : public ISerializable<QJsonObject>
{
public:
	bool deserialize(const QJsonObject &) noexcept override;
	QJsonObject serialize() const override;

	QString getName() const;
	QString getDosage() const;
	QString getFrequency_of_medication() const;
	QString getTerm_of_taking() const;
	QString getNotes() const;
	InjectionType getType() const;

	void setName(const QString &value);
	void setDosage(const QString &value);
	void setFrequency_of_medication(const QString &value);
	void setTerm_of_taking(const QString &value);
	void setNotes(const QString &value);
	void setType(const InjectionType &value);

private:
	QString name;
	QString dosage;
	InjectionType type;
	QString frequency_of_medication;
	QString term_of_taking;
	QString notes;
};

class Prescribings : public ISerializable<QJsonArray>
{
public:
	bool deserialize(const QJsonArray &json) noexcept override;
	QJsonArray serialize() const override;
	bool append(const Medicine &med);
	bool remove(const QString &med_name);
	int size() const;
	Medicine at(QString key) const;
	QStringList keys() const;
private:
	QMap<QString, Medicine> prescribings;
};

