#include "gender.h"
#include "json_fields.h"


bool Gender::deserialize(const QJsonValue& json) noexcept
{
    QString v = json.toString();
    bool is_ok = false;

    if (v == GenderType::gender_male)
    {
        current = GenderEnum::Male;
        is_ok = true;
    }
    else if (v == GenderType::gender_female)
    {
        current = GenderEnum::Female;
        is_ok = true;
    }
    else if (v == GenderType::gender_other)
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
            value = GenderType::gender_male;
            break;
        case GenderEnum::Female:
            value = GenderType::gender_female;
            break;
        case GenderEnum::Other:
            value = GenderType::gender_other;
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
