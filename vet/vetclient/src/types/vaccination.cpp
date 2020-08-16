#include <QVariant>
#include <QDebug>

#include "vaccination.h"
#include "json_fields.h"

bool Vaccination::deserialize(const QJsonObject &json) noexcept
{
	bool cast = true;
	vac_id = json.value(VaccinationJson::field_vac_id).toVariant().toULongLong(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << VaccinationJson::field_vac_id << "' field";
		return false;
	}

	if (against.deserialize(json.value(VaccinationJson::field_vac_against)) == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << VaccinationJson::field_vac_against << "' field";
		return false;
	}

	reg_num = json.value(VaccinationJson::field_vac_reg_num).toString();

	vac_date = QDate::fromString(json.value(VaccinationJson::field_vac_vac_date).toString(), Qt::ISODate);
	if (vac_date.isValid() == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << VaccinationJson::field_vac_vac_date << "' field";
		return false;
	}

	// may be invalid
	next_vac = QDate::fromString(json.value(VaccinationJson::field_vac_next_vac).toString(), Qt::ISODate);

	cast = animal.deserialize(json.value(VaccinationJson::field_vac_animal).toObject());
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << VaccinationJson::field_vac_animal << "' field";
		return false;
	}

	cast = vet.deserialize(json.value(VaccinationJson::field_vac_vet).toObject());
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << VaccinationJson::field_vac_vet << "' field";
		return false;
	}

	return cast;
}

QJsonObject Vaccination::serialize() const
{
	QJsonObject root_obj;
	root_obj.insert(VaccinationJson::field_vac_id, QJsonValue::fromVariant(QVariant::fromValue(vac_id)));
	root_obj.insert(VaccinationJson::field_vac_against, QVariant(against.serialize()).toJsonValue());
	root_obj.insert(VaccinationJson::field_vac_reg_num, QJsonValue(reg_num));
	root_obj.insert(VaccinationJson::field_vac_vac_date, QJsonValue(vac_date.toString(Qt::ISODate)));
	root_obj.insert(VaccinationJson::field_vac_next_vac, QJsonValue(next_vac.toString(Qt::ISODate)));
	root_obj.insert(VaccinationJson::field_vac_animal, animal.serialize());
	root_obj.insert(VaccinationJson::field_vac_vet, vet.serialize());
	return root_obj;
}

uint64_t Vaccination::getVac_id() const
{
	return vac_id;
}

VaccinationAgainst Vaccination::getAgainst() const
{
	return against;
}

void Vaccination::setAgainst(const VaccinationAgainst &value)
{
	against = value;
}

QString Vaccination::getReg_num() const
{
	return reg_num;
}

void Vaccination::setReg_num(const QString &value)
{
	reg_num = value;
}

QDate Vaccination::getVac_date() const
{
	return vac_date;
}

void Vaccination::setVac_date(const QDate &value)
{
	vac_date = value;
}

QDate Vaccination::getNext_vac() const
{
	return next_vac;
}

void Vaccination::setNext_vac(const QDate &value)
{
	next_vac = value;
}

AnimalMedicalRecord Vaccination::getAnimal() const
{
	return animal;
}

void Vaccination::setAnimal(const AnimalMedicalRecord &value)
{
	animal = value;
}

Staff Vaccination::getVet() const
{
	return vet;
}

void Vaccination::setVet(const Staff &value)
{
	vet = value;
}

bool VaccinationAgainst::deserialize(const QJsonValue &json) noexcept
{
	QString v = json.toString();
	bool is_ok = false;
	if (v == VaccinationAgainstType::vacc_against_rab)
	{
		current = VaccinationAgainstEnum::Rab;
		is_ok = true;
	}
	else if (v == VaccinationAgainstType::vacc_against_inf)
	{
		current = VaccinationAgainstEnum::Inf;
		is_ok = true;
	}
	return is_ok;
}

QJsonValue VaccinationAgainst::serialize() const
{
	QJsonValue value;
	switch (current)
	{
		case VaccinationAgainstEnum::Rab:
			value = VaccinationAgainstType::vacc_against_rab;
			break;
		case VaccinationAgainstEnum::Inf:
			value = VaccinationAgainstType::vacc_against_inf;
			break;
	}
	return value;
}

VaccinationAgainst::VaccinationAgainstEnum VaccinationAgainst::getVaccinationAgainst() const
{
	return current;
}

void VaccinationAgainst::setVaccinationAgainst(VaccinationAgainst::VaccinationAgainstEnum value)
{
	current = value;
}
