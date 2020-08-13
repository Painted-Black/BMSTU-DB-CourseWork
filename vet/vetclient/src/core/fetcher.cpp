#include <QMutex>
#include <QNetworkReply>
#include "fetcher.h"

Fetcher::Fetcher()
{
	manager.reset(new QNetworkAccessManager());
	connect(manager.get(), &QNetworkAccessManager::finished, this, &Fetcher::finish);
}

void Fetcher::httpGet(const QString& file, Fetcher::Callback cb)
{
	QFile __F(file);
	if (__F.open(QIODevice::ReadOnly))
	{
		auto data = std::make_unique<QByteArray>(__F.readAll());
		cb(200, std::move(data));
		__F.close();
	}
	else
	{
		cb(403, std::make_unique<QByteArray>("Fuck this shit"));
	}
}

void Fetcher::httpPost(const QString & file, const QByteArray & body, Fetcher::Callback cb)
{
	QFile __F(file);
	if (__F.open(QIODevice::WriteOnly))
	{
		__F.write(body);
		__F.close();
		cb(201, std::make_unique<QByteArray>());
	}
	else
	{
		cb(403, std::make_unique<QByteArray>());
	}
}

void Fetcher::httpPut(const QString & file, const QByteArray & data, Fetcher::Callback cb)
{
	QFile __F(file);
	if (__F.exists() == false)
	{
		cb(403, std::make_unique<QByteArray>("Nothing to do"));
		return;
	}

	if (__F.open(QIODevice::WriteOnly))
	{
		__F.write(data);
		__F.close();
		cb(201, std::make_unique<QByteArray>(data));
	}
	else
	{
		cb(403, std::make_unique<QByteArray>());
	}
}

void Fetcher::httpGet(const QNetworkRequest& req, Fetcher::Callback cb)
{
	QNetworkReply* r = manager->get(req);
	listeners.insert(r, cb);
}

void Fetcher::httpPost(const QNetworkRequest &req, const QByteArray& body, Callback cb)
{
	QNetworkReply* r = manager->post(req, body);
	listeners.insert(r, cb);
}

void Fetcher::httpPut(const QNetworkRequest & req, const QByteArray& data, Fetcher::Callback cb)
{
	QNetworkReply* r = manager->put(req, data);
	listeners.insert(r, cb);
}

void Fetcher::httpDelete(const QNetworkRequest & req, Fetcher::Callback cb)
{
	QNetworkReply* r = manager->deleteResource(req);
	listeners.insert(r, cb);
}

void Fetcher::finish(QNetworkReply *reply)
{
	auto value = std::make_unique<QByteArray>(reply->readAll());
	QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	if (statusCode.isNull())
	{
		return;
	}

	bool cast = 0;
	uint32_t code = statusCode.toUInt(&cast);
	if (cast == false)
	{
		return;
	}

	listeners[reply](code, std::move(value));
}
