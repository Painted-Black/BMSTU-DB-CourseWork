#pragma once

#include <QString>
#include "QJsonHeaders.h"

#include "core/iserializable.h"

class Position final : public ISerializable<QJsonObject>
{
public:
	bool deserialize(const QJsonObject&) noexcept override;
	QJsonObject serialize() const override;

	bool operator==(const Position& p) const;

	uint64_t getId() const;
	QString getTitle() const;
	uint32_t getSalary() const;

	void setTitle(const QString &value);
	void setSalary(const uint32_t &value);

	void setId(const uint64_t &value);

private:
	uint64_t id;
	QString title;
	uint32_t salary;
};

