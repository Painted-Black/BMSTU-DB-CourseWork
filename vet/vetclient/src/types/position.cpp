#include <QVariant>
#include <QDebug>

#include "position.h"
#include "json_fields.h"

bool Position::deserialize(const QJsonObject &obj) noexcept
{
	bool cast = true;
	id = obj.value(PositionJson::field_pos_id).toVariant().toULongLong(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << PositionJson::field_pos_id << "' field";
		return false;
	}

	title = obj.value(PositionJson::field_pos_title).toString();
	salary = obj.value(PositionJson::field_pos_salary).toVariant().toUInt(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast '" << PositionJson::field_pos_salary << "' field";
		return false;
	}

	return true;
}

QJsonObject Position::serialize() const
{
	QJsonObject root_obj;
	root_obj.insert(PositionJson::field_pos_id, QJsonValue::fromVariant(QVariant::fromValue(id)));
	root_obj.insert(PositionJson::field_pos_title, QJsonValue(title));
	root_obj.insert(PositionJson::field_pos_salary, QJsonValue::fromVariant(QVariant::fromValue(salary)));
	return root_obj;
}

bool Position::operator==(const Position &p) const
{
	return (p.id == id && p.title == title && p.salary == salary);
}

QString Position::getTitle() const
{
	return title;
}

void Position::setTitle(const QString &value)
{
	title = value;
}

uint32_t Position::getSalary() const
{
	return salary;
}

void Position::setSalary(const uint32_t &value)
{
	salary = value;
}

void Position::setId(const uint64_t &value)
{
    id = value;
}

uint64_t Position::getId() const
{
    return id;
}
