#include <QVariant>
#include <QDebug>

#include "animal_medical_record.h"

bool AnimalMedicalRecord::deserialize(const QJsonObject &json) noexcept
{
    bool cast = true;
    anim_id = json.value("anim_id").toVariant().toULongLong(&cast);
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'anim_id' field";
        return false;
    }

    name = json.value("name").toString();

    breed = json.value("breed").toString();

    species = json.value("species").toString();

    species = json.value("species").toString();

    if (sex.deserialize(json.value("sex")) == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'sex' field";
        return false;
    }

    castrated = json.value("castrated").toVariant().toBool();

    birth = QDate::fromString(json.value("birth").toString(), Qt::ISODate);
    if (birth.isValid() == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'birth' field";
        return false;
    }

    other_data = json.value("other_data").toString();

    color = json.value("color").toString();

    special_signs = json.value("special_signs").toString();

    registr_date = QDate::fromString(json.value("registr_date").toString(), Qt::ISODate);
    if (registr_date.isValid() == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'registr_date' field";
        return false;
    }

    last_visit = QDate::fromString(json.value("last_visit").toString(), Qt::ISODate);
    if (last_visit.isValid() == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'last_visit' field";
        return false;
    }

    cast = chip.deserialize(json.value("chip_id").toObject());
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast 'chip_id' field";
        return false;
    }

    cast = contract.deserialize(json.value("contract").toObject());
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast 'contract' field";
        return false;
    }

    rel_path_to_photo = json.value("rel_path_to_photo").toString();

    return true;
}

QJsonObject AnimalMedicalRecord::serialize() const
{
    QJsonObject root_obj;
    root_obj.insert("anim_id", QJsonValue::fromVariant(QVariant::fromValue(anim_id)));
    root_obj.insert("name", QJsonValue(name));
    root_obj.insert("breed", QJsonValue(breed));
    root_obj.insert("species", QJsonValue(species));
    root_obj.insert("sex", QVariant(sex.serialize()).toJsonValue());
    root_obj.insert("castrated", QJsonValue::fromVariant(QVariant::fromValue(castrated)));
    root_obj.insert("birth", QJsonValue(birth.toString(Qt::ISODate)));
    root_obj.insert("other_data", QJsonValue(other_data));
    root_obj.insert("color", QJsonValue(color));
    root_obj.insert("special_signs", QJsonValue(special_signs));
    root_obj.insert("registr_date", QJsonValue(registr_date.toString(Qt::ISODate)));
    root_obj.insert("last_visit", QJsonValue(last_visit.toString(Qt::ISODate)));
    root_obj.insert("chip_id", QVariant(chip.serialize()).toJsonValue());
    root_obj.insert("contract", QVariant(contract.serialize()).toJsonValue());
    root_obj.insert("rel_path_to_photo", QJsonValue(rel_path_to_photo));
    return root_obj;
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
