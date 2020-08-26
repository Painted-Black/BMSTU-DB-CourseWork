#include <QVariant>
#include <QDebug>

#include "visit.h"
#include "json_fields.h"

bool Visit::deserialize(const QJsonObject &json) noexcept
{
	bool cast = true;
	vis_id = json.value(VisitJson::field_vis_id).toVariant().toULongLong(&cast);

	cast = doctor.deserialize(json.value(VisitJson::field_vis_doctor).toObject());
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << VisitJson::field_vis_doctor << "' field";
		return false;
	}

	cast = animal.deserialize(json.value(VisitJson::field_vis_animal).toObject());
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << VisitJson::field_vis_animal << "' field";
		return false;
	}

	ambulatury = json.value(VisitJson::field_vis_ambulatury).toVariant().toBool();
	initial = json.value(VisitJson::field_vis_initial).toVariant().toBool();

	visit_date = QDate::fromString(json.value(VisitJson::field_vis_visit_date).toString(), Qt::ISODate);
	if (visit_date.isValid() == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << VisitJson::field_vis_visit_date << "' field";
		return false;
	}

	cast = owner_dynamics.deserialize(json.value(VisitJson::field_vis_owner_dynamics));
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << VisitJson::field_vis_owner_dynamics << "' field";
		return false;
	}

	history_disease = json.value(VisitJson::field_vis_history_disease).toString();

	cast = cur_state.deserialize(json.value(VisitJson::field_vis_cur_state).toObject());
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << VisitJson::field_vis_cur_state << "' field";
		return false;
	}

	diagnosis = json.value(VisitJson::field_vis_diagnosis).toString();

	recommendations = json.value(VisitJson::field_vis_recommendations).toString();

	next_visit = QDate::fromString(json.value(VisitJson::field_vis_next_visit).toString(), Qt::ISODate);

	cast = prescribings.deserialize(json.value(VisitJson::field_vis_prescribings).toArray());
	if (cast == false)
	{
		qCritical() << Q_FUNC_INFO << "invalid cast '" << VisitJson::field_vis_prescribings << "' field";
		return false;
	}

	note = json.value(VisitJson::field_vis_note).toString();
	return true;
}

QJsonObject Visit::serialize() const
{
	QJsonObject root_obj;
	root_obj.insert(VisitJson::field_vis_id, QJsonValue::fromVariant(QVariant::fromValue(vis_id)));
	root_obj.insert(VisitJson::field_vis_doctor, doctor.serialize());
	root_obj.insert(VisitJson::field_vis_animal, animal.serialize());
	root_obj.insert(VisitJson::field_vis_ambulatury, QJsonValue::fromVariant(QVariant::fromValue(ambulatury)));
	root_obj.insert(VisitJson::field_vis_initial, QJsonValue::fromVariant(QVariant::fromValue(initial)));
	root_obj.insert(VisitJson::field_vis_visit_date, QJsonValue(visit_date.toString(Qt::ISODate)));
	root_obj.insert(VisitJson::field_vis_owner_dynamics, owner_dynamics.serialize());
	root_obj.insert(VisitJson::field_vis_history_disease, QJsonValue(history_disease));
	root_obj.insert(VisitJson::field_vis_cur_state, cur_state.serialize());
	root_obj.insert(VisitJson::field_vis_history_disease, QJsonValue(history_disease));
	root_obj.insert(VisitJson::field_vis_diagnosis, QJsonValue(diagnosis));
	root_obj.insert(VisitJson::field_vis_recommendations, QJsonValue(recommendations));
	root_obj.insert(VisitJson::field_vis_next_visit, QJsonValue(next_visit.toString(Qt::ISODate)));
	root_obj.insert(VisitJson::field_vis_prescribings, prescribings.serialize());
	root_obj.insert(VisitJson::field_vis_note, QJsonValue(note));
	return root_obj;
}

uint64_t Visit::getVis_id() const
{
	return vis_id;
}

Staff Visit::getDoctor() const
{
	return doctor;
}

void Visit::setDoctor(const Staff &value)
{
	doctor = value;
}

AnimalMedicalRecord Visit::getAnimal() const
{
	return animal;
}

void Visit::setAnimal(const AnimalMedicalRecord &value)
{
	animal = value;
}

bool Visit::getAmbulatury() const
{
	return ambulatury;
}

void Visit::setAmbulatury(bool value)
{
	ambulatury = value;
}

QDate Visit::getVisit_date() const
{
	return visit_date;
}

void Visit::setVisit_date(const QDate &value)
{
	visit_date = value;
}

OwnerDynamic Visit::getOwner_dynamics() const
{
	return owner_dynamics;
}

void Visit::setOwner_dynamics(const OwnerDynamic &value)
{
	owner_dynamics = value;
}

QString Visit::getHistory_disease() const
{
	return history_disease;
}

void Visit::setHistory_disease(const QString &value)
{
	history_disease = value;
}

AnimalState Visit::getCur_state() const
{
	return cur_state;
}

void Visit::setCur_state(const AnimalState &value)
{
	cur_state = value;
}

QString Visit::getDiagnosis() const
{
	return diagnosis;
}

void Visit::setDiagnosis(const QString &value)
{
	diagnosis = value;
}

QString Visit::getRecommendations() const
{
	return recommendations;
}

void Visit::setRecommendations(const QString &value)
{
	recommendations = value;
}

QDate Visit::getNext_visit() const
{
	return next_visit;
}

void Visit::setNext_visit(const QDate &value)
{
	next_visit = value;
}

Prescribings Visit::getPrescribings() const
{
	return prescribings;
}

void Visit::setPrescribings(const Prescribings &value)
{
	prescribings = value;
}

bool Visit::getInitial() const
{
	return initial;
}

void Visit::setInitial(bool value)
{
	initial = value;
}

QString Visit::getNote() const
{
	return note;
}

void Visit::setNote(const QString &value)
{
	note = value;
}

bool OwnerDynamic::deserialize(const QJsonValue &json) noexcept
{
	QString v = json.toString();
	bool is_ok = false;
	if (v == OwnerDynamicsType::owner_dynamics_stably)
	{
		current = OwnerDynamicEnum::Stably;
		is_ok = true;
	}
	else if (v == OwnerDynamicsType::owner_dynamics_worse)
	{
		current = OwnerDynamicEnum::Worse;
		is_ok = true;
	}
	else if (v == OwnerDynamicsType::owner_dynamics_better)
	{
		current = OwnerDynamicEnum::Better;
		is_ok = true;
	}
	return is_ok;
}

QJsonValue OwnerDynamic::serialize() const
{
	QJsonValue value;
	switch (current)
	{
		case OwnerDynamicEnum::Stably:
			value = OwnerDynamicsType::owner_dynamics_stably;
			break;
		case OwnerDynamicEnum::Worse:
			value = OwnerDynamicsType::owner_dynamics_worse;
			break;
		case OwnerDynamicEnum::Better:
			value = OwnerDynamicsType::owner_dynamics_better;
			break;
	}
	return value;
}

OwnerDynamic::OwnerDynamicEnum OwnerDynamic::getOwnerDynamic() const
{
	return current;
}

void OwnerDynamic::setOwnerDynamic(OwnerDynamic::OwnerDynamicEnum value)
{
	current = value;
}

bool OwnerDynamic::fromString(QString dyn)
{
	OwnerDynamicEnum value;
	bool is_ok = false;
	if (dyn == RusOwnerDynamicsType::rus_owner_dynamics_stably)
	{
		value = OwnerDynamicEnum::Stably;
		is_ok = true;
	}
	else if (dyn == RusOwnerDynamicsType::rus_owner_dynamics_better)
	{
		value = OwnerDynamicEnum::Better;
		is_ok = true;
	}
	else if (dyn == RusOwnerDynamicsType::rus_owner_dynamics_worse)
	{
		value = OwnerDynamicEnum::Worse;
		is_ok = true;
	}
	if (is_ok == true)
	{
		current = value;
	}
	return is_ok;
}

QString OwnerDynamic::toString()
{
	QString value;
	switch (current)
	{
		case OwnerDynamicEnum::Stably:
			value = RusOwnerDynamicsType::rus_owner_dynamics_stably;
			break;
		case OwnerDynamicEnum::Worse:
			value = RusOwnerDynamicsType::rus_owner_dynamics_worse;
			break;
		case OwnerDynamicEnum::Better:
			value = RusOwnerDynamicsType::rus_owner_dynamics_better;
			break;
	}
	return value;
}
