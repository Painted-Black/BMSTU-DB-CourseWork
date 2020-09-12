#pragma once
#include <QDir>
#include <QUrl>
#include <QPixmap>
#include "utils/singlenton.h"

class ImageLoader final
{
public:
	ImageLoader(const QUrl&, std::chrono::milliseconds, const QString&, const QDir& = QDir::temp());
	static void init(const QUrl&, std::chrono::milliseconds, const QString&, const QDir& = QDir::temp());
	static ImageLoader& getInstance();

	QPixmap loadPixmap(const QString&, const QByteArray&);
	std::tuple<bool, QByteArray> saveFromFile(const QString&, const QByteArray &);

private:
	ImageLoader() = default;

private:
	QDir dir;
	QUrl url;
	std::chrono::milliseconds tout;
};

