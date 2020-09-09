#include <QVariant>
#include "short_animal_info.h"
#include "json_fields.h"

QJsonObject ShortAnimalInfo::serialize() const
{
	QJsonObject root_obj;
	root_obj.insert(AnimalMedicalRecordJson::field_anim_id,
					QJsonValue::fromVariant(QVariant::fromValue(uid)));
	root_obj.insert(AnimalMedicalRecordJson::field_anim_name, name);
	root_obj.insert(AnimalMedicalRecordJson::field_anim_species, spec);
	root_obj.insert(AnimalMedicalRecordJson::field_anim_birth, birth.toString(Qt::ISODate));
	root_obj.insert(AnimalMedicalRecordJson::field_anim_rel_path_to_photo, relative_to_file_path);
	return root_obj;
}

bool ShortAnimalInfo::deserialize(const QJsonObject & json) noexcept
{
	uid = json.value(AnimalMedicalRecordJson::field_anim_id).toVariant().value<uint64_t>();
	name = json.value(AnimalMedicalRecordJson::field_anim_name).toString();
	spec = json.value(AnimalMedicalRecordJson::field_anim_species).toString();
	birth = QDate::fromString(
				json.value(AnimalMedicalRecordJson::field_anim_birth).toString(), Qt::ISODate);
	relative_to_file_path = json.value(AnimalMedicalRecordJson::field_anim_rel_path_to_photo).toString();
	return true;
}

uint64_t ShortAnimalInfo::getUid() const
{
	return uid;
}

void ShortAnimalInfo::setUid(uint64_t value)
{
	uid = value;
}

const QString &ShortAnimalInfo::getName() const
{
	return name;
}

void ShortAnimalInfo::setName(const QString &value)
{
	name = value;
}

const QString &ShortAnimalInfo::getSpec() const
{
	return spec;
}

void ShortAnimalInfo::setSpec(const QString &value)
{
	spec = value;
}

const QDate &ShortAnimalInfo::getBirth() const
{
	return birth;
}

void ShortAnimalInfo::setBirth(const QDate &value)
{
	birth = value;
}

const QString &ShortAnimalInfo::getRelativeToFilePath() const
{
    return relative_to_file_path;
}

void ShortAnimalInfo::setRelativeToFilePath(const QString &value)
{
    relative_to_file_path = value;
}
