#include <QVariant>
#include <QDebug>

#include "position.h"



Position::Position()
	: id(10)
{

}

bool Position::deserialize(const QJsonObject &obj) noexcept
{
	bool cast = true;
	id = obj.value("pos_id").toVariant().toULongLong(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast 'pos_id' field";
		return false;
	}

	title = obj.value("title").toString();
	salary = obj.value("salary").toVariant().toUInt(&cast);
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "Invalid cast 'salary' field";
		return false;
	}

	return true;
}

QJsonObject Position::serialize() const
{
	QJsonObject root_obj;
	root_obj.insert("pos_id", QJsonValue::fromVariant(QVariant::fromValue(id)));
	root_obj.insert("title", QJsonValue(title));
	root_obj.insert("salary", QJsonValue::fromVariant(QVariant::fromValue(salary)));
	return root_obj;
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

uint64_t Position::getId() const
{
	return id;
}
