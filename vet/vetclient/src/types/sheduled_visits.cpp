#include "sheduled_visits.h""
#include "json_fields.h"

QJsonObject SheduledVisits::serialize() const
{
//unused
}

bool SheduledVisits::deserialize(const QJsonObject &json) noexcept
{
	date = QDate::fromString(json.value(VisitJson::field_vis_next_visit).toString(), Qt::ISODate);
	animal_name = json.value(AnimalMedicalRecordJson::field_anim_name).toString();
	animal_species = json.value(AnimalMedicalRecordJson::field_anim_species).toString();
	return true;
}

QDate SheduledVisits::getDate() const
{
	return date;
}

void SheduledVisits::setDate(const QDate &value)
{
	date = value;
}

QString SheduledVisits::getAnimalSpecies() const
{
	return animal_species;
}

void SheduledVisits::setAnimalSpecies(const QString &value)
{
	animal_species = value;
}

QString SheduledVisits::getAnimalName() const
{
	return animal_name;
}

void SheduledVisits::setAnimalName(const QString &value)
{
	animal_name = value;
}
