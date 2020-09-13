#pragma once

#include <chrono>
#include <memory>
#include <QSettings>
#include <QUrl>

class Config final
{
public:
	bool loadConfig(const QString&) noexcept;

	std::chrono::milliseconds getTimeout() const noexcept;
	QUrl getUrlAuthication() const noexcept;
	QUrl getUrlAnimal() const noexcept;
	QUrl getUrlClient() const noexcept;
	QUrl getUrlAnimalsShortInfo() const noexcept;
	QUrl getUrlClientsShortInfo() const noexcept;
	QUrl getUrlAddAnimal() const noexcept;
	QUrl getUrlCurrentvisits() const noexcept;
	QUrl getUrlNewVisit() const noexcept;
	QUrl getUrlSystemUsersList() const noexcept;
	QUrl getUrlDeleteUser() const noexcept;
	QUrl getUrlStaffShortInfo() const noexcept;
	QUrl getUrlAddUser() const noexcept;
	QUrl getUrlUpdateUser() const noexcept;
	QUrl getUrlAllPositions() const noexcept;
	QUrl getUrlUpdatePosition() const noexcept;
	QUrl getUrlAddPosition() const noexcept;
	QUrl getUrlStaffFullInfo() const noexcept;
	QUrl getUrlPhotoData() const noexcept;
	QUrl getUrlFireStaff() const noexcept;
	QUrl getUrlAddStaff() const noexcept;
	QUrl getUrlUpdateStaff() const noexcept;
	QUrl getUrlScheduleStaff() const noexcept;
	QUrl getUrlAllSchedules() const noexcept;
	QUrl getUrlAllVisitsShort() const noexcept;
	QUrl getUrlVisitFull() const noexcept;

private:
	QUrl getUrl(const QString&) const;

private:
	std::unique_ptr<QSettings> config;
};

