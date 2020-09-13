#include <QFile>
#include <QDebug>
#include "config.h"

bool Config::loadConfig(const QString & file) noexcept
{
	if (QFile::exists(file) == false)
	{
		qCritical().noquote() << QString("Config file '%1' not found").arg(file);
		return false;
	}

	config.reset(new QSettings(file, QSettings::IniFormat));
	return true;
}

std::chrono::milliseconds Config::getTimeout() const noexcept
{
	bool cast = true;
	uint64_t timeout = config->value("SERVER/timeout").toULongLong(&cast);
	Q_ASSERT(cast);
	return decltype (getTimeout())(timeout);
}

QUrl Config::getUrlAuthication() const noexcept
{
	return getUrl("ROUTES/auth");
}

QUrl Config::getUrlAnimal() const noexcept
{
	return getUrl("ROUTES/animals");
}

QUrl Config::getUrlClient() const noexcept
{
	return getUrl("ROUTES/client_data");
}

QUrl Config::getUrlAnimalsShortInfo() const noexcept
{
	return getUrl("ROUTES/animals_short_info");
}

QUrl Config::getUrlClientsShortInfo() const noexcept
{
	return getUrl("ROUTES/clients_short_info");
}

QUrl Config::getUrlAddAnimal() const noexcept
{
	return getUrl("ROUTES/animals_add");
}

QUrl Config::getUrlCurrentvisits() const noexcept
{
	return getUrl("ROUTES/current_visits");
}

QUrl Config::getUrlNewVisit() const noexcept
{
	return getUrl("ROUTES/new_visit");
}

QUrl Config::getUrlSystemUsersList() const noexcept
{
	return getUrl("ROUTES/system_users_list");
}

QUrl Config::getUrlDeleteUser() const noexcept
{
	return getUrl("ROUTES/delete_user");
}

QUrl Config::getUrlStaffShortInfo() const noexcept
{
	return getUrl("ROUTES/staff_short");
}

QUrl Config::getUrlAddUser() const noexcept
{
	return getUrl("ROUTES/add_user");
}

QUrl Config::getUrlUpdateUser() const noexcept
{
	return getUrl("ROUTES/update_user");
}

QUrl Config::getUrlAllPositions() const noexcept
{
	return getUrl("ROUTES/all_positions");
}

QUrl Config::getUrlUpdatePosition() const noexcept
{
	return getUrl("ROUTES/update_position");
}

QUrl Config::getUrlAddPosition() const noexcept
{
	return getUrl("ROUTES/add_position");
}

QUrl Config::getUrlStaffFullInfo() const noexcept
{
	return getUrl("ROUTES/full_staff_info");
}

QUrl Config::getUrlPhotoData() const noexcept
{
	return getUrl("ROUTES/image_data");
}

QUrl Config::getUrlFireStaff() const noexcept
{
	return getUrl("ROUTES/fire_staff");
}

QUrl Config::getUrlAddStaff() const noexcept
{
	return getUrl("ROUTES/add_staff");
}

QUrl Config::getUrlUpdateStaff() const noexcept
{
	return getUrl("ROUTES/update_staff");
}

QUrl Config::getUrlScheduleStaff() const noexcept
{
	return getUrl("ROUTES/post_schedule");
}

QUrl Config::getUrlAllSchedules() const noexcept
{
	return getUrl("ROUTES/all_schedules");
}

QUrl Config::getUrlContract() const noexcept
{
	return getUrl("ROUTES/contract");
}

QUrl Config::getUrl(const QString & path) const
{
	QUrl url;
	url.setScheme("http");
	url.setHost(config->value("SERVER/ip").toString());

	bool cast = true;
	int port = config->value("SERVER/port").toInt(&cast);
	Q_ASSERT(cast);

	url.setPort(port);
	url.setPath(config->value(path).toString());
	Q_ASSERT(url.isValid());

	return url;
}

