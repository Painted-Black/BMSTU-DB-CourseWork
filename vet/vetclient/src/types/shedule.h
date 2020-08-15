#pragma once

#include <QString>
#include <QDateTime>
#include "QJsonHeaders.h"

#include "core/ISerializable.h"

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
    DayOfWeek getDay_of_week() const;
    QString getType() const;
    QDateTime getStart() const;
    QDateTime getEnd() const;
    QString getCabinet() const;

    void setDay_of_week(const DayOfWeek &value);
    void setType(const QString &value);
    void setStart(const QDateTime &value);
    void setEnd(const QDateTime &value);
    void setCabinet(const QString &value);

private:
    uint64_t shed_id;
    DayOfWeek day_of_week;
    QDateTime start;
    QDateTime end;
    QString cabinet;
};

class SheduleList final : public ISerializable<QJsonArray>
{
public:
    bool deserialize(const QJsonArray &jarray) noexcept override;
    QJsonArray serialize() const override;
    void add_shedule_item(Shedule& shed);

    QList<Shedule> getShedule_list() const;

private:
    QList<Shedule> shedule_list;
};


