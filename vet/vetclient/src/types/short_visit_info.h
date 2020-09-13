#pragma once

#include <QDate>
#include "types/QJsonHeaders.h"
#include "core/iserializable.h"

class ShortVisitInfo : public ISerializable<QJsonObject>
{
public:
	virtual QJsonObject serialize() const override;
	virtual bool deserialize(const QJsonObject &json) noexcept override;
	QDate visitDate() const;
	void setVisitDate(const QDate &visitDate);

	uint64_t visitId() const;
	void setVisitId(const uint64_t &visitId);

	QString docName() const;
	void setDocName(const QString &docName);

	QString docPatr() const;
	void setDocPatr(const QString &docPatr);

	QString docSurname() const;
	void setDocSurname(const QString &docSurname);

	QString docFio() const;
	void setDocFio(const QString &docFio);

	QString animalName() const;
	void setAnimalName(const QString &animalName);

	QString animalSpecies() const;
	void setAnimalSpecies(const QString &animalSpecies);

private:
	QDate mVisitDate;
	uint64_t mVisitId;
	QString mDocName;
	QString mDocSurname;
	QString mDocPatr;
	QString mDocFio;
	QString mAnimalName;
	QString mAnimalSpecies;
};

