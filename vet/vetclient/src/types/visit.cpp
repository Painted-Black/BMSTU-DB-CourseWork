#include "visit.h"

bool Visit::deserialize(const QJsonObject &) noexcept
{
#pragma message "TODO"
}

QJsonObject Visit::serialize() const
{
#pragma message "TODO"
}

bool OwnerDynamic::deserialize(const QJsonValue &json) noexcept
{
    QString v = json.toString();
    bool is_ok = false;
    if (v == "stably")
    {
        current = OwnerDynamicEnum::Stably;
        is_ok = true;
    }
    else if (v == "worse")
    {
        current = OwnerDynamicEnum::Worse;
        is_ok = true;
    }
    else if (v == "better")
    {
        current = OwnerDynamicEnum::Better;
        is_ok = true;
    }
    return is_ok;
}

QJsonValue OwnerDynamic::serialize() const
{
    QJsonValue value;
    switch (current)
    {
        case OwnerDynamicEnum::Stably:
            value = "stably";
            break;
        case OwnerDynamicEnum::Worse:
            value = "worse";
            break;
        case OwnerDynamicEnum::Better:
            value = "better";
            break;
    }
    return value;
}

OwnerDynamic::OwnerDynamicEnum OwnerDynamic::getOwnerDynamic() const
{
    return current;
}

void OwnerDynamic::setOwnerDynamic(OwnerDynamic::OwnerDynamicEnum value)
{
    current = value;
}
