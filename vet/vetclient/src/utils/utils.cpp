#include <QWidget>
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

bool compareAnimalRecordsWithoutClientInfo(
		const AnimalMedicalRecord &first,
		const AnimalMedicalRecord &second)
{
	bool is_compare = true;
	const auto& chip_1 = first.getChip();
	const auto& chip_2 = second.getChip();
	const auto& contr_1 = first.getContract();
	const auto& contr_2 = second.getContract();

	is_compare &= contr_1.getCode() == contr_2.getCode();
	is_compare &= contr_1.getContrId() == contr_2.getContrId();
	is_compare &= contr_1.getValidUntil() == contr_2.getValidUntil();
	is_compare &= contr_1.getConclusionDate() == contr_2.getConclusionDate();
	is_compare &= chip_1 == chip_2;

	is_compare &= first.getSex() == second.getSex();
	is_compare &= first.getName() == second.getName();
	is_compare &= first.getBirth() == second.getBirth();
	is_compare &= first.getBreed() == second.getBreed();
	is_compare &= first.getColor() == second.getColor();
	is_compare &= first.getAnimId() == second.getAnimId();
	is_compare &= first.getSpecies() == second.getSpecies();
	is_compare &= first.getCastrated() == second.getCastrated();
	is_compare &= first.getLastVisit() == second.getLastVisit();
	is_compare &= first.getOtherData() == second.getOtherData();
	is_compare &= first.getRegistrDate() == second.getRegistrDate();

	return is_compare;
}

void removeClientInfoFromAnimalRecord(QJsonObject & object)
{
	QJsonObject root_json = object[AnimalMedicalRecordJson::field_anim_contract].toObject();
	root_json.remove(ContractJson::field_contr_owner);
	object.insert(AnimalMedicalRecordJson::field_anim_contract, root_json);
}

void centredWidget(QWidget * widget, const QRect& screen)
{
	auto width = widget->width();
	auto height = widget->height();
	int x = (screen.width() - width) / 2;
	int y = (screen.height() - height) / 2;

	widget->setGeometry(x, y, width, height);
}

QByteArray accessSerialize(const AccessData &acc)
{
	QJsonObject root_obj;
	QJsonObject staff_incomplete_obj;
	staff_incomplete_obj.insert(StaffJson::field_staff_id, QJsonValue::fromVariant(QVariant::fromValue(acc.getOwner().getId())));
	root_obj.insert(AccessJson::field_acc_employee, staff_incomplete_obj);
	root_obj.insert(AccessJson::field_acc_login, QJsonValue(acc.getLogin()));
	root_obj.insert(AccessJson::field_acc_password, QJsonValue::fromVariant((QVariant(acc.getPassword()))));
	root_obj.insert(AccessJson::field_acc_access_level, QJsonValue(acc.getLevel().toString()));
	return QJsonDocument(root_obj).toJson();
}

QString initials(const QString &name, const QString &surname, const QString &patr)
{
	QString initials = surname;
	if (name.size() >= 1)
	{
		initials += " ";
		initials += name.at(0);
		initials += ".";
	}
	if (patr.size() >= 1)
	{
		initials += " ";
		initials += patr.at(0);
		initials += ".";
	}
	return initials;
}
