#pragma once

#include <QString>
#include <QDate>

#include "QJsonHeaders.h"
#include "core/ISerializable.h"
#include "staff.h"
#include "animal_medical_record.h"
#include "animalstate.h"
#include "prescribings.h"

class OwnerDynamic : public ISerializable<QJsonValue>
{
public:
	enum class OwnerDynamicEnum
	{
		Stably,
		Worse,
		Better
	};
public:
	bool deserialize(const QJsonValue&json) noexcept override;
	QJsonValue serialize() const override;

	OwnerDynamicEnum getOwnerDynamic() const;
	void setOwnerDynamic(OwnerDynamicEnum value);

private:
	OwnerDynamicEnum current;
};

class Visit : public ISerializable<QJsonObject>
{
public:
	bool deserialize(const QJsonObject &json) noexcept override;
	QJsonObject serialize() const override;

	uint64_t getVis_id() const;
	Staff getDoctor() const;
	AnimalMedicalRecord getAnimal() const;
	bool getAmbulatury() const;
	QDate getVisit_date() const;
	OwnerDynamic getOwner_dynamics() const;
	QString getHistory_disease() const;
	AnimalState getCur_state() const;
	QString getDiagnosis() const;
	QString getRecommendations() const;
	QDate getNext_visit() const;
	Prescribings getPrescribings() const;
	bool getInitial() const;
	QString getNote() const;

	void setDoctor(const Staff &value);
	void setAnimal(const AnimalMedicalRecord &value);
	void setAmbulatury(bool value);
	void setVisit_date(const QDate &value);
	void setOwner_dynamics(const OwnerDynamic &value);
	void setHistory_disease(const QString &value);
	void setCur_state(const AnimalState &value);
	void setDiagnosis(const QString &value);
	void setRecommendations(const QString &value);
	void setNext_visit(const QDate &value);
	void setPrescribings(const Prescribings &value);
	void setInitial(bool value);
	void setNote(const QString &value);

private:
	uint64_t vis_id;
	Staff doctor;
	AnimalMedicalRecord animal;
	bool ambulatury;
	QDate visit_date;
	OwnerDynamic owner_dynamics;
	QString history_disease;
	AnimalState cur_state;
	QString diagnosis;
	QString recommendations;
	QDate next_visit;
	Prescribings prescribings;
	bool initial;
	QString note;
};

