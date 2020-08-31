#include <QVariant>
#include <QDebug>

#include "animal_medical_record.h"
#include "json_fields.h"

bool AnimalMedicalRecord::deserialize(const QJsonObject &json) noexcept
{
	bool cast = true;
	anim_id = json.value(AnimalMedicalRecordJson::field_anim_id).toVariant().toULongLong(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << AnimalMedicalRecordJson::field_anim_id << "' field";
	}

	name = json.value(AnimalMedicalRecordJson::field_anim_name).toString();
	breed = json.value(AnimalMedicalRecordJson::field_anim_breed).toString();

	species = json.value(AnimalMedicalRecordJson::field_anim_species).toString();
	castrated = json.value(AnimalMedicalRecordJson::field_anim_castrated).toVariant().toBool();
	birth = QDate::fromString(json.value(AnimalMedicalRecordJson::field_anim_birth).toString(), Qt::ISODate);
	other_data = json.value(AnimalMedicalRecordJson::field_anim_other_data).toString();
	color = json.value(AnimalMedicalRecordJson::field_anim_color).toString();
	special_signs = json.value(AnimalMedicalRecordJson::field_anim_specil_signs).toString();
	registr_date = QDate::fromString(json.value(AnimalMedicalRecordJson::field_anim_registr_date).toString(), Qt::ISODate);
	last_visit = QDate::fromString(json.value(AnimalMedicalRecordJson::field_anim_last_visit).toString(), Qt::ISODate);
	rel_path_to_photo = json.value(AnimalMedicalRecordJson::field_anim_rel_path_to_photo).toString();

	cast &= registr_date.isValid();
	cast &= birth.isValid();
	cast &= last_visit.isValid();

	if (sex.deserialize(json.value(AnimalMedicalRecordJson::field_anim_sex)) == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << AnimalMedicalRecordJson::field_anim_sex << "' field";
	}

	cast = chip.deserialize(json.value(AnimalMedicalRecordJson::field_anim_chip_id).toObject());
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << AnimalMedicalRecordJson::field_anim_chip_id << "' field";
	}

	cast = contract.deserialize(json.value(AnimalMedicalRecordJson::field_anim_contract).toObject());
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << AnimalMedicalRecordJson::field_anim_contract << "' field";
	}

	return cast;
}

QJsonObject AnimalMedicalRecord::serialize() const
{
	QJsonObject root_obj;
	root_obj.insert(AnimalMedicalRecordJson::field_anim_id, QJsonValue::fromVariant(QVariant::fromValue(anim_id)));
	root_obj.insert(AnimalMedicalRecordJson::field_anim_name, QJsonValue(name));
	root_obj.insert(AnimalMedicalRecordJson::field_anim_breed, QJsonValue(breed));
	root_obj.insert(AnimalMedicalRecordJson::field_anim_species, QJsonValue(species));
	root_obj.insert(AnimalMedicalRecordJson::field_anim_sex, QVariant(sex.serialize()).toJsonValue());
	root_obj.insert(AnimalMedicalRecordJson::field_anim_castrated, QJsonValue::fromVariant(QVariant::fromValue(castrated)));
	root_obj.insert(AnimalMedicalRecordJson::field_anim_birth, QJsonValue(birth.toString(Qt::ISODate)));
	root_obj.insert(AnimalMedicalRecordJson::field_anim_other_data, QJsonValue(other_data));
	root_obj.insert(AnimalMedicalRecordJson::field_anim_color, QJsonValue(color));
	root_obj.insert(AnimalMedicalRecordJson::field_anim_specil_signs, QJsonValue(special_signs));
	root_obj.insert(AnimalMedicalRecordJson::field_anim_registr_date, QJsonValue(registr_date.toString(Qt::ISODate)));
	root_obj.insert(AnimalMedicalRecordJson::field_anim_last_visit, QJsonValue(last_visit.toString(Qt::ISODate)));
	root_obj.insert(AnimalMedicalRecordJson::field_anim_chip_id, QVariant(chip.serialize()).toJsonValue());
	root_obj.insert(AnimalMedicalRecordJson::field_anim_contract, QVariant(contract.serialize()).toJsonValue());
	root_obj.insert(AnimalMedicalRecordJson::field_anim_rel_path_to_photo, QJsonValue(rel_path_to_photo));
	return root_obj;
}

uint64_t AnimalMedicalRecord::getAnimId() const
{
	return anim_id;
}

const QString &AnimalMedicalRecord::getName() const
{
	return name;
}

void AnimalMedicalRecord::setName(const QString &value)
{
	name = value;
}

const QString &AnimalMedicalRecord::getBreed() const
{
	return breed;
}

void AnimalMedicalRecord::setBreed(const QString &value)
{
	breed = value;
}

const QString &AnimalMedicalRecord::getSpecies() const
{
	return species;
}

void AnimalMedicalRecord::setSpecies(const QString &value)
{
	species = value;
}

const Gender &AnimalMedicalRecord::getSex() const
{
	return sex;
}

void AnimalMedicalRecord::setSex(const Gender &value)
{
	sex = value;
}

bool AnimalMedicalRecord::getCastrated() const
{
	return castrated;
}

void AnimalMedicalRecord::setCastrated(bool value)
{
	castrated = value;
}

const QDate &AnimalMedicalRecord::getBirth() const
{
	return birth;
}

void AnimalMedicalRecord::setBirth(const QDate &value)
{
	birth = value;
}

const QString &AnimalMedicalRecord::getOtherData() const
{
	return other_data;
}

void AnimalMedicalRecord::setOtherData(const QString &value)
{
	other_data = value;
}

const QString &AnimalMedicalRecord::getColor() const
{
	return color;
}

void AnimalMedicalRecord::setColor(const QString &value)
{
	color = value;
}

const QString &AnimalMedicalRecord::getSpecialSigns() const
{
	return special_signs;
}

void AnimalMedicalRecord::setSpecialSigns(const QString &value)
{
	special_signs = value;
}

const QDate &AnimalMedicalRecord::getRegistrDate() const
{
	return registr_date;
}

void AnimalMedicalRecord::setRegistrDate(const QDate &value)
{
	registr_date = value;
}

const QDate &AnimalMedicalRecord::getLastVisit() const
{
	return last_visit;
}

void AnimalMedicalRecord::setLastVisit(const QDate &value)
{
	last_visit = value;
}

Microchip &AnimalMedicalRecord::getChip()
{
	return chip;
}

Contract &AnimalMedicalRecord::getContract()
{
	return contract;
}

const QString &AnimalMedicalRecord::getRelPathToPhoto() const
{
	return rel_path_to_photo;
}

bool AnimalMedicalRecord::operator==(const AnimalMedicalRecord & v) const
{
	bool is_equal = true;
	is_equal &= (name == v.name);
	is_equal &= (breed == v.breed);
	is_equal &= (species == v.species);
	is_equal &= (sex == v.sex);
	is_equal &= (birth == v.birth);
	is_equal &= (other_data == v.other_data);
	is_equal &= (color == v.color);
	is_equal &= (special_signs == v.special_signs);
	is_equal &= (registr_date == v.registr_date);
	is_equal &= (last_visit == v.last_visit);
	is_equal &= (chip == v.chip);
	is_equal &= (contract == v.contract);
	is_equal &= (rel_path_to_photo == v.rel_path_to_photo);
	is_equal &= (castrated == v.castrated);

	return is_equal;
}

void AnimalMedicalRecord::setAnimId(uint64_t id)
{
	anim_id = id;
}

void AnimalMedicalRecord::setRelPathToPhoto(const QString &value)
{
	rel_path_to_photo = value;
}
