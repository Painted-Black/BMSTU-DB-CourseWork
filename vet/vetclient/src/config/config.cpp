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

QUrl Config::getUrlAnimalsShortInfo() const noexcept
{
	return getUrl("ROUTES/animals_short_info");
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

