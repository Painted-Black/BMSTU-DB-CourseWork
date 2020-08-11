#include <QVariant>
#include <QDebug>

#include "animalstate.h"

bool AnimalState::deserialize(const QJsonObject &json) noexcept
{
    bool cast = true;
    state_id = json.value("state_id").toVariant().toULongLong(&cast);
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'state_id' field";
        return false;
    }

    cast = general.deserialize(json.value("general").toObject());
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast 'general' field";
        return false;
    }

    pulse = json.value("pulse").toVariant().toULongLong(&cast);
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'pulse' field";
        return false;
    }

    weight = json.value("weight").toVariant().toFloat(&cast);
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'weight' field";
        return false;
    }

    AP = json.value("ap").toString();

    temperature = json.value("temperature").toVariant().toFloat(&cast);
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'temperature' field";
        return false;
    }

    cfr = json.value("cfr").toVariant().toULongLong(&cast);
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'cfr' field";
        return false;
    }

    resp_rate = json.value("resp_rate").toVariant().toULongLong(&cast);
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'resp_rate' field";
        return false;
    }
    return true;
}

QJsonObject AnimalState::serialize() const
{
    QJsonObject root_obj;
    root_obj.insert("staff_id", QJsonValue::fromVariant(QVariant::fromValue(state_id)));
    root_obj.insert("general", QVariant(general.serialize()).toJsonValue());
    root_obj.insert("pulse", QJsonValue::fromVariant(QVariant::fromValue(pulse)));
    root_obj.insert("weight", QJsonValue::fromVariant(QVariant::fromValue(weight)));
    root_obj.insert("ap", QJsonValue::fromVariant(QVariant::fromValue(AP)));
    root_obj.insert("temperature", QJsonValue::fromVariant(QVariant::fromValue(temperature)));
    root_obj.insert("cfr", QJsonValue::fromVariant(QVariant::fromValue(cfr)));
    root_obj.insert("resp_rate", QJsonValue::fromVariant(QVariant::fromValue(resp_rate)));
    return root_obj;
}

uint64_t AnimalState::getState_id() const
{
    return state_id;
}

GeneralState AnimalState::getGeneral() const
{
    return general;
}

void AnimalState::setGeneral(const GeneralState &value)
{
    general = value;
}

uint32_t AnimalState::getPulse() const
{
    return pulse;
}

void AnimalState::setPulse(const uint32_t &value)
{
    pulse = value;
}

float AnimalState::getWeight() const
{
    return weight;
}

void AnimalState::setWeight(float value)
{
    weight = value;
}

QString AnimalState::getAP() const
{
    return AP;
}

void AnimalState::setAP(const QString &value)
{
    AP = value;
}

float AnimalState::getTemperature() const
{
    return temperature;
}

void AnimalState::setTemperature(float value)
{
    temperature = value;
}

uint32_t AnimalState::getCfr() const
{
    return cfr;
}

void AnimalState::setCfr(const uint32_t &value)
{
    cfr = value;
}

uint32_t AnimalState::getResp_rate() const
{
    return resp_rate;
}

void AnimalState::setResp_rate(const uint32_t &value)
{
    resp_rate = value;
}

bool GeneralState::deserialize(const QJsonValue &json) noexcept
{
    bool is_ok = false;
    QString v = json.toString();
    if (v == "middle")
    {
        current = GeneralStateEnum::Middle;
        is_ok = true;
    }
    else if (v == "good")
    {
        current = GeneralStateEnum::Good;
        is_ok = true;
    }
    else if (v == "bad")
    {
        current = GeneralStateEnum::Bad;
        is_ok = true;
    }
    return is_ok;
}

QJsonValue GeneralState::serialize() const
{
    QJsonValue value;
    switch (current)
    {
        case GeneralStateEnum::Middle:
            value = "middle";
            break;
        case GeneralStateEnum::Good:
            value = "good";
            break;
        case GeneralStateEnum::Bad:
            value = "bad";
            break;
    }
    return value;
}

GeneralState::GeneralStateEnum GeneralState::getAnimalState() const
{
    return current;
}

void GeneralState::setAnimalState(GeneralState::GeneralStateEnum value)
{
    current = value;
}
