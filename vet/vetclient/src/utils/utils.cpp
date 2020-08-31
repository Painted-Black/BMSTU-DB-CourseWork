#include <QJsonDocument>
#include "utils.h"

QByteArray toJson(const QJsonObject & obj) noexcept
{
	return QJsonDocument(obj).toJson();
}


QJsonObject fromJson(const QByteArray & json) noexcept
{
	return QJsonDocument::fromJson(json).object();
}

QJsonArray fromJsonArray(const QByteArray & json) noexcept
{
	return QJsonDocument::fromJson(json).array();
}

QMap<QString, QString> fromSimpleJson(const QByteArray &json) noexcept
{
	QMap<QString, QString> out;
	QJsonObject json_obj = fromJson(json);
	QStringList keys = json_obj.keys();
	for (const QString& key : keys)
	{
		out[key] = json_obj[key].toString();
	}
	return out;
}

QByteArray visitSerialize(const Visit& vis, uint32_t anim_id)
{
	QJsonObject root_obj;
	QJsonObject animal_incomplete_obj;
	animal_incomplete_obj.insert(AnimalMedicalRecordJson::field_anim_id, QJsonValue::fromVariant(QVariant::fromValue(anim_id)));
	root_obj.insert(VisitJson::field_vis_doctor, vis.getDoctor().serialize());
	root_obj.insert(VisitJson::field_vis_animal, animal_incomplete_obj);
	root_obj.insert(VisitJson::field_vis_visit_date, QJsonValue(vis.getVisit_date().toString(Qt::ISODate)));
	root_obj.insert(VisitJson::field_vis_owner_dynamics, vis.getOwner_dynamics().serialize());
	root_obj.insert(VisitJson::field_vis_history_disease, QJsonValue(vis.getHistory_disease()));
	root_obj.insert(VisitJson::field_vis_cur_state, vis.getCur_state().serialize());
	root_obj.insert(VisitJson::field_vis_diagnosis, QJsonValue(vis.getDiagnosis()));
	root_obj.insert(VisitJson::field_vis_recommendations, QJsonValue(vis.getRecommendations()));
	if (vis.getNext_visit().isValid() == true)
	{
		root_obj.insert(VisitJson::field_vis_next_visit, QJsonValue(vis.getNext_visit().toString(Qt::ISODate)));
	}
	else
	{
		root_obj.insert(VisitJson::field_vis_next_visit, QJsonValue());
	}
	root_obj.insert(VisitJson::field_vis_prescribings, vis.getPrescribings().serialize());
	root_obj.insert(VisitJson::field_vis_note, QJsonValue(vis.getNote()));
	return QJsonDocument(root_obj).toJson();
//	root_obj.insert(VisitJson::field_vis_ambulatury, QJsonValue::fromVariant(QVariant::fromValue(vis.getAmbulatury())));
//	root_obj.insert()
}
