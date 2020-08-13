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
        return false;
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

    init_soft = cast;

    if (sex.deserialize(json.value(AnimalMedicalRecordJson::field_anim_sex)) == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast '" << AnimalMedicalRecordJson::field_anim_sex << "' field";
        return false;
    }

    cast = chip.deserialize(json.value(AnimalMedicalRecordJson::field_anim_chip_id).toObject());
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast '" << AnimalMedicalRecordJson::field_anim_chip_id << "' field";
        return false;
    }

    cast = contract.deserialize(json.value(AnimalMedicalRecordJson::field_anim_contract).toObject());
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast '" << AnimalMedicalRecordJson::field_anim_contract << "' field";
        return false;
    }

    init_full = cast;

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

bool AnimalMedicalRecord::isSoftInit() const
{
    return init_soft;
}

bool AnimalMedicalRecord::isInit() const
{
    return init_full;
}

uint64_t AnimalMedicalRecord::getAnim_id() const
{
    return anim_id;
}

QString AnimalMedicalRecord::getName() const
{
    return name;
}

void AnimalMedicalRecord::setName(const QString &value)
{
    name = value;
}

QString AnimalMedicalRecord::getBreed() const
{
    return breed;
}

void AnimalMedicalRecord::setBreed(const QString &value)
{
    breed = value;
}

QString AnimalMedicalRecord::getSpecies() const
{
    return species;
}

void AnimalMedicalRecord::setSpecies(const QString &value)
{
    species = value;
}

Gender AnimalMedicalRecord::getSex() const
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

QDate AnimalMedicalRecord::getBirth() const
{
    return birth;
}

void AnimalMedicalRecord::setBirth(const QDate &value)
{
    birth = value;
}

QString AnimalMedicalRecord::getOther_data() const
{
    return other_data;
}

void AnimalMedicalRecord::setOther_data(const QString &value)
{
    other_data = value;
}

QString AnimalMedicalRecord::getColor() const
{
    return color;
}

void AnimalMedicalRecord::setColor(const QString &value)
{
    color = value;
}

QString AnimalMedicalRecord::getSpecial_signs() const
{
    return special_signs;
}

void AnimalMedicalRecord::setSpecial_signs(const QString &value)
{
    special_signs = value;
}

QDate AnimalMedicalRecord::getRegistr_date() const
{
    return registr_date;
}

void AnimalMedicalRecord::setRegistr_date(const QDate &value)
{
    registr_date = value;
}

QDate AnimalMedicalRecord::getLast_visit() const
{
    return last_visit;
}

void AnimalMedicalRecord::setLast_visit(const QDate &value)
{
    last_visit = value;
}

Microchip AnimalMedicalRecord::getChip() const
{
    return chip;
}

void AnimalMedicalRecord::setChip(const Microchip &value)
{
    chip = value;
}

Contract AnimalMedicalRecord::getContract() const
{
    return contract;
}

void AnimalMedicalRecord::setContract(const Contract &value)
{
    contract = value;
}

QString AnimalMedicalRecord::getRel_path_to_photo() const
{
    return rel_path_to_photo;
}

void AnimalMedicalRecord::setRel_path_to_photo(const QString &value)
{
    rel_path_to_photo = value;
}
