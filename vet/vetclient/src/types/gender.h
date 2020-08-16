#pragma once

#include "QJsonHeaders.h"
#include "core/ISerializable.h"

class Gender : public ISerializable<QJsonValue>
{
public:
	enum class GenderEnum
	{
		Male,
		Female,
		Other
	};
public:
	bool deserialize(const QJsonValue&) noexcept override;
	QJsonValue serialize() const override;

	GenderEnum getGenderType() const;
	void setGenderType(GenderEnum value);
	QString toString();

private:
	GenderEnum current;
};
