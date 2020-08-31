#pragma once

#include <QString>
#include <QDate>

#include "QJsonHeaders.h"
#include "core/iserializable.h"
#include "gender.h"
#include "microchip.h"
#include "contract.h"

class AnimalMedicalRecord final : public ISerializable<QJsonObject>
{
public:
	bool deserialize(const QJsonObject &json) noexcept override;
	QJsonObject serialize() const override;

	uint64_t getAnimId() const;
	const QString& getName() const;
	const QString& getBreed() const;
	const QString& getSpecies() const;
	const Gender& getSex() const;
	bool getCastrated() const;
	const QDate& getBirth() const;
	const QString& getOtherData() const;
	const QString& getColor() const;
	const QString& getSpecialSigns() const;
	const QDate& getRegistrDate() const;
	const QDate& getLastVisit() const;
	Microchip& getChip();
	Contract& getContract();
	const QString& getRelPathToPhoto() const;

	bool operator== (const AnimalMedicalRecord&) const;

	void setAnimId(uint64_t);
	void setName(const QString &value);
	void setBreed(const QString &value);
	void setSpecies(const QString &value);
	void setSex(const Gender &value);
	void setCastrated(bool value);
	void setBirth(const QDate &value);
	void setOtherData(const QString &value);
	void setColor(const QString &value);
	void setSpecialSigns(const QString &value);
	void setRegistrDate(const QDate &value);
	void setLastVisit(const QDate &value);
	void setRelPathToPhoto(const QString &value);

	template<typename T>
	void setChip(T &&value)
	{
		chip = std::forward<decltype (chip)>(value);
	}

	template<typename T>
	void setContract(T&&value)
	{
		contract = std::forward<decltype (contract)>(value);
	}
private:
	uint64_t anim_id;
	QString name;
	QString breed;
	QString species;
	Gender sex;
	QDate birth;
	QString other_data;
	QString color;
	QString special_signs;
	QDate registr_date;
	QDate last_visit;
	Microchip chip;
	Contract contract;
	QString rel_path_to_photo;
	bool castrated;
};

