#pragma once

#include <QString>
#include <QDateTime>
#include "QJsonHeaders.h"

#include "core/ISerializable.h"
#include "types/staff.h"

class DayOfWeek : public ISerializable<QJsonValue>
{
public:
    enum class DayOfWeekEnum
    {
        Sun,
        Mon,
        Tue,
        Wed,
        Thu,
        Fri,
        Sat
    };
public:
    bool deserialize(const QJsonValue&json) noexcept override;
    QJsonValue serialize() const override;

    DayOfWeekEnum getDayOfkWeek() const;
    void setDayOfkWeek(DayOfWeekEnum value);

private:
    DayOfWeekEnum current;
};

class Shedule final : public ISerializable<QJsonObject>
{
public:
    bool deserialize(const QJsonObject &json) noexcept override;
    QJsonObject serialize() const override;

    uint64_t getShed_id() const;
    Staff getEmpoyee() const;
    DayOfWeek getDay_of_week() const;
    QString getType() const;
    QDateTime getStart() const;
    QDateTime getEnd() const;
    QString getCabinet() const;

    void setEmpoyee(const Staff &value);
    void setDay_of_week(const DayOfWeek &value);
    void setType(const QString &value);
    void setStart(const QDateTime &value);
    void setEnd(const QDateTime &value);
    void setCabinet(const QString &value);

private:
    uint64_t shed_id;
    Staff empoyee;
    DayOfWeek day_of_week;
    QString type;
    QDateTime start;
    QDateTime end;
    QString cabinet;
};

