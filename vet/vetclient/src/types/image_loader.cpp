#include <QDebug>
#include "image_loader.h"
#include "core/network/network_fetcher.h"

static std::unique_ptr<ImageLoader> loader;

void ImageLoader::init(const QUrl& u, std::chrono::milliseconds t, const QString& r, const QDir& d)
{
	loader.reset(new ImageLoader(u, t, r, d));
}

ImageLoader &ImageLoader::getInstance()
{
	return *loader;
}

ImageLoader::ImageLoader(const QUrl& u, std::chrono::milliseconds t, const QString &root_dir, const QDir & directory)
	: url(u), tout(t)
{
	dir = directory;
	dir.mkdir(root_dir);
	dir.cd(root_dir);
}

QPixmap ImageLoader::loadPixmap(const QString &filename, const QByteArray& key)
{
	auto files = dir.entryInfoList(QDir::Files, QDir::Name | QDir::IgnoreCase);

	for (const auto& file : files)
	{
		if (file.baseName() == filename)
		{
			return QPixmap(file.filePath());
		}
	}

	url.setQuery(QString("img=%1").arg(filename));
	QNetworkRequest req(url);
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(key));

	NetworkFetcher fetcher;
	auto reply = fetcher.httpGet(req, tout);
	if (std::get<0>(reply) != 200)
	{
		return QPixmap();
	}
	else
	{
		QString content_type;
		for (const auto& header : std::get<3>(reply))
		{
			if (std::get<0>(header)== "Content-Type")
			{
				content_type = std::get<1>(header);
				break;
			}
		}

		QFile file;
		if (content_type == "image/jpeg")
		{
			file.setFileName(dir.filePath(filename + ".jpeg"));
		}
		else if (content_type == "image/png")
		{
			file.setFileName(dir.filePath(filename + ".png"));
		}

		if (file.open(QIODevice::WriteOnly) == false)
		{
			return QPixmap();
		}

		file.write(std::get<2>(reply));
		file.close();

		QPixmap out;
		out.loadFromData(std::get<2>(reply));
		return out;
	}
}

std::tuple<bool, QByteArray> ImageLoader::saveFromFile(const QString& file, const QByteArray& p)
{
	if (QFile::exists(file) == false)
	{
		qCritical() << Q_FUNC_INFO << file;
		return { false, "" };
	}

	QFileInfo file_info(file);
	QString content_type;
	QString file_ext = file_info.suffix();
	if (file_ext == "png")
	{
		content_type="image/png";
	}
	else if (file_ext == "jpeg" || file_ext == "jpg")
	{
		content_type = "image/jpeg";
	}
	else
	{
		return { false, "" };
	}

	QFile f(file);
	if (f.open(QIODevice::ReadOnly) == false)
	{
		return { false, "" };
	}

	QNetworkRequest req(url);
	req.setHeader(QNetworkRequest::ContentTypeHeader, content_type);
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(p));
	NetworkFetcher fetcher;
	auto reply = fetcher.httpPost(req, f.readAll(), tout);
	if (std::get<0>(reply) != 201)
	{
		f.close();
		return { false, "" };
	}

	auto new_file = std::get<2>(reply);
	f.copy(new_file);
	f.close();
	return { true, new_file };
}
