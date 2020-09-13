#include "short_visit_info.h"
#include "types/json_fields.h"
#include "utils/utils.h"

QJsonObject ShortVisitInfo::serialize() const
{
	QJsonObject root_obj;
//	unused
	return root_obj;
}

bool ShortVisitInfo::deserialize(const QJsonObject &json) noexcept
{
	bool is_ok = true;

	mVisitId = json.value(VisitJson::field_vis_id).toVariant().value<uint64_t>();
	mVisitDate = QDate::fromString(json.value(VisitJson::field_vis_visit_date).toString(), Qt::ISODate);

	QJsonObject staff_obj = json.value(VisitJson::field_vis_doctor).toObject();
	QJsonObject passport_obj = staff_obj.value(StaffJson::field_staff_passport).toObject();

	mDocName = passport_obj.value(PassportJson::field_pass_name).toString();
	mDocSurname = passport_obj.value(PassportJson::field_pass_surname).toString();
	mDocPatr = passport_obj.value(PassportJson::field_pass_patronymic).toString();
	mDocFio = initials(mDocName, mDocSurname, mDocPatr);

	QJsonObject anim_rec_obj = json.value(VisitJson::field_vis_animal).toObject();

	mAnimalName = anim_rec_obj.value(AnimalMedicalRecordJson::field_anim_name).toString();
	mAnimalSpecies = anim_rec_obj.value(AnimalMedicalRecordJson::field_anim_species).toString();

	return is_ok;
}

QDate ShortVisitInfo::visitDate() const
{
	return mVisitDate;
}

void ShortVisitInfo::setVisitDate(const QDate &visitDate)
{
	mVisitDate = visitDate;
}

uint64_t ShortVisitInfo::visitId() const
{
	return mVisitId;
}

void ShortVisitInfo::setVisitId(const uint64_t &visitId)
{
	mVisitId = visitId;
}

QString ShortVisitInfo::docName() const
{
	return mDocName;
}

void ShortVisitInfo::setDocName(const QString &docName)
{
	mDocName = docName;
}

QString ShortVisitInfo::docPatr() const
{
	return mDocPatr;
}

void ShortVisitInfo::setDocPatr(const QString &docPatr)
{
	mDocPatr = docPatr;
}

QString ShortVisitInfo::docSurname() const
{
	return mDocSurname;
}

void ShortVisitInfo::setDocSurname(const QString &docSurname)
{
	mDocSurname = docSurname;
}

QString ShortVisitInfo::docFio() const
{
	return mDocFio;
}

void ShortVisitInfo::setDocFio(const QString &docFio)
{
	mDocFio = docFio;
}

QString ShortVisitInfo::animalName() const
{
	return mAnimalName;
}

void ShortVisitInfo::setAnimalName(const QString &animalName)
{
	mAnimalName = animalName;
}

QString ShortVisitInfo::animalSpecies() const
{
    return mAnimalSpecies;
}

void ShortVisitInfo::setAnimalSpecies(const QString &animalSpecies)
{
    mAnimalSpecies = animalSpecies;
}
