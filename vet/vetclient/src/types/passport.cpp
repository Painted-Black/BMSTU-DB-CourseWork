#include <QVariant>
#include <QDebug>

#include "passport.h"

bool Passport::deserialize(const QJsonObject &obj) noexcept
{
    bool cast = true;
    id = obj.value("pass_id").toVariant().toULongLong(&cast);
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'pass_id' field";
        return false;
    }

    surname = obj.value("surname").toString();
    name = obj.value("name").toString();
    patronymic = obj.value("patronymic").toString();
    if (gender.deserialize(obj.value("sex")) == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'gender' field";
        return false;
    }
    // 2020-12-20T12:40:40 (yyyy-mm-ddThh:MM:ss)
    birthday = QDate::fromString(obj.value("birth").toString(), Qt::ISODate);
    if (birthday.isValid() == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'birth' field";
        return false;
    }

    QString num = obj.value("num").toString();
    std::copy(num.cbegin(), num.cend(), passport_num.begin());
    issue_date = QDate::fromString(obj.value("issue_date").toString(), Qt::ISODate);
    if (issue_date.isValid() == false)
    {
        qCritical() << Q_FUNC_INFO << "Invalid cast 'issue_date' field";
        return false;
    }

    nationality = obj.value("nationality").toString();
    return true;
}

QJsonObject Passport::serialize() const
{
    QJsonObject root_obj;
    root_obj.insert("pass_id", QJsonValue::fromVariant(QVariant::fromValue(id)));
    root_obj.insert("surname", QJsonValue(surname));
    root_obj.insert("name", QJsonValue(name));
    root_obj.insert("patronymic", QJsonValue(patronymic));

    root_obj.insert("sex", QVariant(gender.serialize()).toJsonValue());
    root_obj.insert("birth", QJsonValue(birthday.toString(Qt::ISODate)));
    root_obj.insert("issue_date", QJsonValue(issue_date.toString(Qt::ISODate)));
    root_obj.insert("nationality", QJsonValue(nationality));
    root_obj.insert("num", QJsonValue(QString(passport_num.data(),
                                              static_cast<int>(passport_num.size()))));
    return root_obj;
}

uint64_t Passport::getId() const
{
    return id;
}

QString Passport::getSurname() const
{
    return surname;
}

void Passport::setSurname(const QString &value)
{
    surname = value;
}

QString Passport::getName() const
{
    return name;
}

void Passport::setName(const QString &value)
{
    name = value;
}

QString Passport::getPatronymic() const
{
    return patronymic;
}

void Passport::setPatronymic(const QString &value)
{
    patronymic = value;
}

QDate Passport::getBirthday() const
{
    return birthday;
}

void Passport::setBirthday(const QDate &value)
{
    birthday = value;
}

QDate Passport::getIssue_date() const
{
    return issue_date;
}

void Passport::setIssue_date(const QDate &value)
{
    issue_date = value;
}

QString Passport::getNationality() const
{
    return nationality;
}

void Passport::setNationality(const QString &value)
{
    nationality = value;
}

QString Passport::getPassport_num() const
{
    return passport_num;
}

void Passport::setPassport_num(const QString &value)
{
    passport_num = value;
}

Gender Passport::getGender() const
{
    return gender;
}

void Passport::setGender(const Gender &value)
{
    gender = value;
}

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
