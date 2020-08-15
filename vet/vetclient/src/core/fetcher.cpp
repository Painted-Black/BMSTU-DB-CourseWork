#include <QMutex>
#include <QNetworkReply>
#include "fetcher.h"

Fetcher::Fetcher()
{
	manager.reset(new QNetworkAccessManager());
	connect(manager.get(), &QNetworkAccessManager::finished, this, &Fetcher::finish);
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
    auto value = reply->readAll();
    qDebug() << Q_FUNC_INFO << "Exec" << value;
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

    if (listeners.contains(reply))
    {
        listeners[reply](code, value);
    }
}
