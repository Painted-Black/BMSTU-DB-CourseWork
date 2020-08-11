#include "gender.h"


bool Gender::deserialize(const QJsonValue& json) noexcept
{
    QString v = json.toString();
    bool is_ok = false;

    if (v == "m")
    {
        current = GenderEnum::Male;
        is_ok = true;
    }
    else if (v == "f")
    {
        current = GenderEnum::Female;
        is_ok = true;
    }
    else if (v == "other")
    {
        current = GenderEnum::Other;
        is_ok = true;
    }

    return is_ok;
}

QJsonValue Gender::serialize() const
{
    QJsonValue value;
    switch (current)
    {
        case GenderEnum::Male:
            value = "m";
            break;
        case GenderEnum::Female:
            value = "f";
            break;
        case GenderEnum::Other:
            value = "other";
            break;
    }
    return value;
}

Gender::GenderEnum Gender::getGenderType() const
{
    return current;
}

void Gender::setGenderType(GenderEnum value)
{
    current = value;
}
