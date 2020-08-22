#include <QVariant>
#include <QDebug>

#include "prescribings.h"
#include "json_fields.h"

bool InjectionType::deserialize(const QJsonValue &json) noexcept
{
    QString v = json.toString();
    bool is_ok = false;
    if (v == InjectionTypes::injection_intramuscular)
    {
        current = InjectionTypeEnum::Intramuscular;
        is_ok = true;
    }
    else if (v == InjectionTypes::injection_intravenous)
    {
        current = InjectionTypeEnum::Intravenous;
        is_ok = true;
    }
    else if (v == InjectionTypes::injection_subcutaneous)
    {
        current = InjectionTypeEnum::Subcutaneous;
        is_ok = true;
    }
    else if (v == InjectionTypes::injection_ingest)
    {
        current = InjectionTypeEnum::Ingest;
        is_ok = true;
    }
    return is_ok;
}

QJsonValue InjectionType::serialize() const
{
    QJsonValue value;
    switch (current)
    {
        case InjectionTypeEnum::Intravenous:
            value = InjectionTypes::injection_intravenous;
            break;
        case InjectionTypeEnum::Intramuscular:
            value = InjectionTypes::injection_intramuscular;
            break;
        case InjectionTypeEnum::Subcutaneous:
            value =InjectionTypes::injection_subcutaneous;
            break;
        case InjectionTypeEnum::Ingest:
            value = InjectionTypes::injection_ingest;
            break;
    }
    return value;
}

QString InjectionType::toString()
{
    QString value;
    switch (current)
    {
        case InjectionTypeEnum::Intravenous:
            value = RusInjectionTypes::rus_injection_intravenous;
            break;
        case InjectionTypeEnum::Intramuscular:
            value = RusInjectionTypes::rus_injection_intramuscular;
            break;
        case InjectionTypeEnum::Subcutaneous:
            value = RusInjectionTypes::rus_injection_subcutaneous;
            break;
        case InjectionTypeEnum::Ingest:
            value = RusInjectionTypes::rus_injection_ingest;
            break;
    }
    return value;
}

InjectionType::InjectionTypeEnum InjectionType::getInjectionType() const
{
    return current;
}

void InjectionType::setInjectionType(const InjectionTypeEnum &value)
{
    current = value;
}

bool InjectionType::fromString(const QString &type)
{
    InjectionTypeEnum value;
    bool is_ok = false;

    if (type == RusInjectionTypes::rus_injection_ingest)
    {
        value = InjectionTypeEnum::Ingest;
        is_ok = true;
    }
    else if (type == RusInjectionTypes::rus_injection_intravenous)
    {
        value = InjectionTypeEnum::Intravenous;
        is_ok = true;
    }
    else if (type == RusInjectionTypes::rus_injection_subcutaneous)
    {
        value = InjectionTypeEnum::Subcutaneous;
        is_ok = true;
    }
    else if (type == RusInjectionTypes::rus_injection_intramuscular)
    {
        value = InjectionTypeEnum::Intramuscular;
        is_ok = true;
    }
    if (is_ok == true)
    {
        current = value;
    }

    return is_ok;
}

bool Medicine::deserialize(const QJsonObject &json) noexcept
{
	bool cast = true;
	name = json.value(PrescribingsJson::field_prescr_name).toString();
	dosage = json.value(PrescribingsJson::field_prescr_dosage).toString();

    cast = type.deserialize(json.value(PrescribingsJson::field_prescr_type));
    if (cast == false)
    {
        qCritical() << Q_FUNC_INFO << "invalid cast '" << PrescribingsJson::field_prescr_type << "' field";
        return false;
    }

	frequency_of_medication = json.value(PrescribingsJson::field_prescr_frequency_of_medication).toString();
	term_of_taking = json.value(PrescribingsJson::field_prescr_term_of_taking).toString();
	notes = json.value(PrescribingsJson::field_prescr_notes).toString();
	return cast;
}

QJsonObject Medicine::serialize() const
{
	QJsonObject root_obj;
	root_obj.insert(PrescribingsJson::field_prescr_name, QJsonValue(name));
	root_obj.insert(PrescribingsJson::field_prescr_dosage, QJsonValue(dosage));
    root_obj.insert(PrescribingsJson::field_prescr_type, QVariant(type.serialize()).toJsonValue());
	root_obj.insert(PrescribingsJson::field_prescr_frequency_of_medication, QJsonValue(frequency_of_medication));
	root_obj.insert(PrescribingsJson::field_prescr_term_of_taking, QJsonValue(term_of_taking));
	root_obj.insert(PrescribingsJson::field_prescr_name, QJsonValue(notes));
	return root_obj;
}

QString Medicine::getName() const
{
	return name;
}

void Medicine::setName(const QString &value)
{
	name = value;
}

QString Medicine::getDosage() const
{
	return dosage;
}

void Medicine::setDosage(const QString &value)
{
	dosage = value;
}

QString Medicine::getFrequency_of_medication() const
{
	return frequency_of_medication;
}

void Medicine::setFrequency_of_medication(const QString &value)
{
	frequency_of_medication = value;
}

QString Medicine::getTerm_of_taking() const
{
	return term_of_taking;
}

void Medicine::setTerm_of_taking(const QString &value)
{
	term_of_taking = value;
}

QString Medicine::getNotes() const
{
	return notes;
}

void Medicine::setNotes(const QString &value)
{
	notes = value;
}

InjectionType Medicine::getType() const
{
    return type;
}

void Medicine::setType(const InjectionType &value)
{
    type = value;
}

bool Prescribings::deserialize(const QJsonArray &json) noexcept
{
    bool is_ok = false;
    for (const QJsonValue& cur : json)
    {
        Medicine cur_med;
		cur_med.deserialize(cur.toObject());
		is_ok &= append(cur_med);
		if (is_ok == false)
			break;
	}
	return is_ok;
}

QJsonArray Prescribings::serialize() const
{
	QJsonArray root_obj;
	for (const auto& prescribing : prescribings)
	{
		root_obj.push_back(prescribing.serialize());
	}
	return root_obj;
}

bool Prescribings::append(const Medicine &med)
{
	bool is_ok = false;
	if (prescribings.contains(med.getName()) == false)
	{
		prescribings.insert(med.getName(), med);
		is_ok = true;
	}
	return is_ok;
}

bool Prescribings::remove(const QString &med_name)
{
	bool is_ok = false;
	if (prescribings.contains(med_name) == false)
	{
		prescribings.remove(med_name);
		is_ok = true;
	}
    return is_ok;
}

int Prescribings::size() const
{
    return prescribings.size();
}

Medicine Prescribings::at(QString key) const
{
    return prescribings[key];
}

QStringList Prescribings::keys()
{
    return prescribings.keys();
}
