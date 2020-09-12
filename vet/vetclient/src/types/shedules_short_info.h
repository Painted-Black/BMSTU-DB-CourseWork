#pragma once

#include <QDate>
#include "types/QJsonHeaders.h"
#include "core/iserializable.h"
#include "schedule.h"

class ShedulesShortInfo : public ISerializable<QJsonObject>
{
public:
	virtual QJsonObject serialize() const override;
	virtual bool deserialize(const QJsonObject &json) noexcept override;

	ScheduleList schedList() const;
	void setSchedList(const ScheduleList &schedList);

	uint64_t staffId() const;
	void setStaffId(const uint64_t &staffId);

	uint64_t posId() const;
	void setPosId(const uint64_t &posId);

	uint64_t passId() const;
	void setPassId(const uint64_t &passId);

	QString posTitle() const;
	void setPosTitle(const QString &posTitle);

	QString surname() const;
	void setSurname(const QString &surname);

	QString name() const;
	void setName(const QString &name);

	QString patr() const;
	void setPatr(const QString &patr);

	QString fio() const;
	void setFio(const QString &fio);

private:
	ScheduleList mSchedList;
	uint64_t mStaffId;
	uint64_t mPosId;
	uint64_t mPassId;
	QString mPosTitle;
	QString mSurname;
	QString mName;
	QString mPatr;
	QString mFio;
};

