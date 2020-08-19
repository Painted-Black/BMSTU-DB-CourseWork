#pragma once

#include <memory>
#include <curl/curl.h>
#include <QUrl>
#include <QVector>
#include <QNetworkRequest>

class NetworkFetcher
{
	struct RequestInfo;
	struct Info;
public:
	using Header = std::tuple<QString, QByteArray>;
	using AuthData = std::tuple<QString, QString>;
	using Response = std::tuple<int32_t, double, QByteArray, QVector<Header>>;

public:
	NetworkFetcher();
	~NetworkFetcher() noexcept;

	Response httpGet(const QNetworkRequest&, std::chrono::milliseconds);
	Response httpPost(const QNetworkRequest&, const QByteArray&, std::chrono::milliseconds);

private:
	Response performRequest(const QUrl&);
	void setCurlOptions();
	void appendContentLenght(const QNetworkRequest &, size_t);
	QString getUserAgent();
	void setRequest(const QNetworkRequest&, std::chrono::milliseconds, bool = false);

private:
	CURL* curl;
	std::unique_ptr<RequestInfo> req_info;
	std::unique_ptr<Info> info;
};

