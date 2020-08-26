#include <QVariant>
#include <QDebug>

#include "animalstate.h"
#include "json_fields.h"

bool AnimalState::deserialize(const QJsonObject &json) noexcept
{
	bool cast = true;
	state_id = json.value(AnimalStateJson::field_state_id).toVariant().toULongLong(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << AnimalStateJson::field_state_id << "' field";
		return false;
	}

	cast = general.deserialize(json.value(AnimalStateJson::field_state_general).toObject());
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << AnimalStateJson::field_state_general << "' field";
		return false;
	}

	pulse = json.value(AnimalStateJson::field_state_pulse).toVariant().toULongLong(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << AnimalStateJson::field_state_pulse << "' field";
		return false;
	}

	weight = json.value(AnimalStateJson::field_state_weight).toVariant().toFloat(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << AnimalStateJson::field_state_weight << "' field";
		return false;
	}

	AP = json.value(AnimalStateJson::field_state_ap).toString();

	temperature = json.value(AnimalStateJson::field_state_temperature).toVariant().toFloat(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << AnimalStateJson::field_state_temperature << "' field";
		return false;
	}

	cfr = json.value(AnimalStateJson::field_state_cfr).toVariant().toULongLong(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << AnimalStateJson::field_state_cfr << "' field";
		return false;
	}

	resp_rate = json.value(AnimalStateJson::field_state_resp_rate).toVariant().toULongLong(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << AnimalStateJson::field_state_resp_rate << "' field";
		return false;
	}
	return true;
}

QJsonObject AnimalState::serialize() const
{
	QJsonObject root_obj;
	root_obj.insert(AnimalStateJson::field_state_id, QJsonValue::fromVariant(QVariant::fromValue(state_id)));
	root_obj.insert(AnimalStateJson::field_state_general, QVariant(general.serialize()).toJsonValue());
	root_obj.insert(AnimalStateJson::field_state_pulse, QJsonValue::fromVariant(QVariant::fromValue(pulse)));
	root_obj.insert(AnimalStateJson::field_state_weight, QJsonValue::fromVariant(QVariant::fromValue(weight)));
	root_obj.insert(AnimalStateJson::field_state_ap, QJsonValue::fromVariant(QVariant::fromValue(AP)));
	root_obj.insert(AnimalStateJson::field_state_temperature, QJsonValue::fromVariant(QVariant::fromValue(temperature)));
	root_obj.insert(AnimalStateJson::field_state_cfr, QJsonValue::fromVariant(QVariant::fromValue(cfr)));
	root_obj.insert(AnimalStateJson::field_state_resp_rate, QJsonValue::fromVariant(QVariant::fromValue(resp_rate)));
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
	if (v == GeneralStateType::general_state_middle)
	{
		current = GeneralStateEnum::Middle;
		is_ok = true;
	}
	else if (v == GeneralStateType::general_state_good)
	{
		current = GeneralStateEnum::Good;
		is_ok = true;
	}
	else if (v == GeneralStateType::general_state_bad)
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
			value = GeneralStateType::general_state_middle;
			break;
		case GeneralStateEnum::Good:
			value = GeneralStateType::general_state_good;
			break;
		case GeneralStateEnum::Bad:
			value = GeneralStateType::general_state_bad;
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

QString GeneralState::toString()
{
	QString value;
	switch (current)
	{
		case GeneralStateEnum::Middle:
			value = RusGeneralStateType::rus_general_state_middle;
			break;
		case GeneralStateEnum::Good:
			value = RusGeneralStateType::rus_general_state_good;
			break;
		case GeneralStateEnum::Bad:
			value = RusGeneralStateType::rus_general_state_bad;
			break;
	}
	return value;
}

bool GeneralState::fromString(QString state)
{
	bool is_ok = false;
	GeneralStateEnum value;
	if (state == RusGeneralStateType::rus_general_state_middle)
	{
		value = GeneralStateEnum::Middle;
		is_ok = true;
	}
	else if (state == RusGeneralStateType::rus_general_state_good)
	{
		value = GeneralStateEnum::Good;
		is_ok = true;
	}
	else if (state == RusGeneralStateType::rus_general_state_bad)
	{
		value = GeneralStateEnum::Bad;
		is_ok = true;
	}
	if (is_ok == true)
	{
		current = value;
	}
	return is_ok;
}
