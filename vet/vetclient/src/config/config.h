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
	QUrl getUrlAnimalsShortInfo() const noexcept;
	QUrl getUrlAddAnimal() const noexcept;

private:
	QUrl getUrl(const QString&) const;

private:
	std::unique_ptr<QSettings> config;
};

