#pragma once

#include <QString>
#include <QDate>

#include "QJsonHeaders.h"
#include "core/ISerializable.h"
#include "gender.h"
#include "microchip.h"
#include "contract.h"

class AnimalMedicalRecord final : public ISerializable<QJsonObject>
{
public:
    bool deserialize(const QJsonObject &json) noexcept override;
    QJsonObject serialize() const override;

    bool isSoftInit() const;
    bool isInit() const;

    uint64_t getAnim_id() const;
    QString getName() const;
    QString getBreed() const;
    QString getSpecies() const;
    Gender getSex() const;
    bool getCastrated() const;
    QDate getBirth() const;
    QString getOther_data() const;
    QString getColor() const;
    QString getSpecial_signs() const;
    QDate getRegistr_date() const;
    QDate getLast_visit() const;
    Microchip getChip() const;
    Contract getContract() const;
    QString getRel_path_to_photo() const;

    void setName(const QString &value);
    void setBreed(const QString &value);
    void setSpecies(const QString &value);
    void setSex(const Gender &value);
    void setCastrated(bool value);
    void setBirth(const QDate &value);
    void setOther_data(const QString &value);
    void setColor(const QString &value);
    void setSpecial_signs(const QString &value);
    void setRegistr_date(const QDate &value);
    void setLast_visit(const QDate &value);
    void setChip(const Microchip &value);
    void setContract(const Contract &value);
    void setRel_path_to_photo(const QString &value);
private:


private:
    uint64_t anim_id;
    QString name;
    QString breed;
    QString species;
    Gender sex;
    QDate birth;
    QString other_data;
    QString color;
    QString special_signs;
    QDate registr_date;
    QDate last_visit;
    Microchip chip;
    Contract contract;
    QString rel_path_to_photo;
    bool castrated;
    bool init_soft;
    bool init_full;
};

