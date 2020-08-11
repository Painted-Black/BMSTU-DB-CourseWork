#pragma once

#include <QString>
#include <QDate>

#include "QJsonHeaders.h"
#include "core/ISerializable.h"
#include "animal_medical_record.h"
#include "staff.h"

class VaccinationAgainst : public ISerializable<QJsonValue>
{
public:
    enum class VaccinationAgainstEnum
    {
        Rab,
        Inf
    };
public:
    bool deserialize(const QJsonValue&json) noexcept override;
    QJsonValue serialize() const override;

    VaccinationAgainstEnum getVaccinationAgainst() const;
    void setVaccinationAgainst(VaccinationAgainstEnum value);

private:
    VaccinationAgainstEnum current;
};

class Vaccination final: public ISerializable<QJsonObject>
{
public:
    bool deserialize(const QJsonObject &json) noexcept override;
    QJsonObject serialize() const override;

    uint64_t getVac_id() const;
    VaccinationAgainst getAgainst() const;
    QString getReg_num() const;
    QDate getVac_date() const;
    QDate getNext_vac() const;
    AnimalMedicalRecord getAnimal() const;
    Staff getVet() const;

    void setAgainst(const VaccinationAgainst &value);
    void setReg_num(const QString &value);
    void setVac_date(const QDate &value);
    void setNext_vac(const QDate &value);
    void setAnimal(const AnimalMedicalRecord &value);
    void setVet(const Staff &value);

private:
    uint64_t vac_id;
    VaccinationAgainst against;
    QString reg_num;
    QDate vac_date;
    QDate next_vac;
    AnimalMedicalRecord animal;
    Staff vet;
};

