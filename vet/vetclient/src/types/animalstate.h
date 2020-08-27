#pragma once

#include <QString>
#include "QJsonHeaders.h"

#include "core/iserializable.h"

class GeneralState : public ISerializable<QJsonValue>
{
public:
	enum class GeneralStateEnum
	{
		Middle,
		Good,
		Bad
	};
public:
	bool deserialize(const QJsonValue&json) noexcept override;
	QJsonValue serialize() const override;

	GeneralStateEnum getAnimalState() const;
	void setAnimalState(GeneralStateEnum value);
	QString toString();
	bool fromString(QString state);

private:
	GeneralStateEnum current;
};

class AnimalState final : public ISerializable<QJsonObject>
{
public:
	bool deserialize(const QJsonObject &json) noexcept override;
	QJsonObject serialize() const override;

	uint64_t getState_id() const;
	GeneralState getGeneral() const;
	uint32_t getPulse() const;
	float getWeight() const;
	QString getAP() const;
	float getTemperature() const;
	uint32_t getCfr() const;
	uint32_t getResp_rate() const;

	void setGeneral(const GeneralState &value);
	void setPulse(const uint32_t &value);
	void setWeight(float value);
	void setAP(const QString &value);
	void setTemperature(float value);
	void setCfr(const uint32_t &value);
	void setResp_rate(const uint32_t &value);

private:
	uint64_t state_id;
	GeneralState general;
	uint32_t pulse;
	float weight;
	QString AP; // артериальное давление
	float temperature;
	uint32_t cfr; // скорость наполнения капилляров
	uint32_t resp_rate; // частота дыхательных движений
};

