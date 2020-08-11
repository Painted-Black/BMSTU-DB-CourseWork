#pragma once

#include <QList>

#include "QJsonHeaders.h"
#include "core/ISerializable.h"

class InjectionType : public ISerializable<QJsonValue>
{
public:
    enum class InjectionTypeEnum
    {
        Subcutaneous,
        Intravenous,
        Intramuscular,
        Ingest
    };
    bool deserialize(const QJsonValue &json) noexcept override;
    QJsonValue serialize() const override;

    InjectionTypeEnum getInjectionType() const;
    void setInjectionType(const InjectionTypeEnum &value);

private:
    InjectionTypeEnum current;
};

class Medicine : public ISerializable<QJsonObject>
{
public:
    bool deserialize(const QJsonObject &) noexcept override;
    QJsonObject serialize() const override;

    QString getName() const;
    QString getDosage() const;
    InjectionType getType() const;
    QString getFrequency_of_medication() const;
    QString getTerm_of_taking() const;
    QString getNotes() const;

    void setName(const QString &value);
    void setDosage(const QString &value);
    void setType(const InjectionType &value);
    void setFrequency_of_medication(const QString &value);
    void setTerm_of_taking(const QString &value);
    void setNotes(const QString &value);

private:
    QString name;
    QString dosage;
    InjectionType type;
    QString frequency_of_medication;
    QString term_of_taking;
    QString notes;
};

class Prescribings : public ISerializable<QJsonObject>
{
public:
    bool deserialize(const QJsonObject &) noexcept override;
    QJsonObject serialize() const override;
private:
    QList<Medicine> prescribings;
#pragma message "TODO"

};

