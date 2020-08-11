#pragma once

#include <QString>
#include <QDate>

#include "QJsonHeaders.h"
#include "core/ISerializable.h"
#include "staff.h"
#include "animal_medical_record.h"
#include "animalstate.h"

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
    bool deserialize(const QJsonObject &) noexcept override;
    QJsonObject serialize() const override;

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

    bool initial;
    QString note;
};

