#pragma once

#include <memory>
#include <functional>

#include <QMap>
#include <QNetworkAccessManager>

class Fetcher : public QObject
{
	Q_OBJECT
public:
    using Callback = std::function<void(uint32_t, QByteArray)>;
public:
	Fetcher();

    void httpGet(const QNetworkRequest&, Callback);
	void httpPost(const QNetworkRequest&, const QByteArray&, Callback);
	void httpPut(const QNetworkRequest&, const QByteArray&, Callback);
	void httpDelete(const QNetworkRequest&req, Callback);

private:
	void finish(QNetworkReply* rep);


private:
	std::unique_ptr<QNetworkAccessManager> manager;
    QMap<QNetworkReply*, Callback> listeners;
};
