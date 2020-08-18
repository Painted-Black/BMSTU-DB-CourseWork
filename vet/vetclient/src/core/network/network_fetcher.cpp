#include <chrono>
#include <QDebug>
#include "network_fetcher.h"

static auto setopt = &curl_easy_setopt;
static auto getinfo = &curl_easy_getinfo;

struct NetworkFetcher::RequestInfo
{
	double totalTime;
	double nameLookupTime;
	double connectTime;
	double appConnectTime;
	double preTransferTime;
	double startTransferTime;
	double redirectTime;
	int8_t redirectCount;
};

struct NetworkFetcher::Info
{
	QUrl baseUrl;
	QVector<Header> headers;
	std::chrono::milliseconds timeout;
	bool followRedirects;
	int16_t maxRedirects;
	bool noSignal;
	AuthData basicAuth;
	QString certPath;
	QString certType;
	QString keyPath;
	QString keyPassword;
	QString customUserAgent;
	QString uriProxy;
	QString proxyAuth;
	RequestInfo lastRequest;
};

NetworkFetcher::NetworkFetcher():
	req_info(std::make_unique<RequestInfo>()),
	info(std::make_unique<Info>())
{
	curl = curl_easy_init();
	info->timeout= std::chrono::milliseconds(0);
	info->followRedirects = false;
	info->noSignal = false;
	info->maxRedirects = -1l;
}

NetworkFetcher::~NetworkFetcher() noexcept
{
	curl_free(curl);
}

NetworkFetcher::Response NetworkFetcher::httpGet(const QNetworkRequest &req,
												 std::chrono::milliseconds timeout)
{
	setRequest(req, timeout);
	return performRequest(req.url());
}

NetworkFetcher::Response NetworkFetcher::httpPost(const QNetworkRequest & req,
												  const QByteArray & data, std::chrono::milliseconds tout)
{
	size_t size = static_cast<size_t>(data.size());
	setRequest(req, tout, true);
	appendContentLenght(req, size);

	const char* __data = data.data();
	setopt(curl, CURLOPT_POST, 1L);
	setopt(curl, CURLOPT_POSTFIELDS, __data);
	setopt(curl, CURLOPT_POSTFIELDSIZE, size);

	return performRequest(req.url());
}

extern "C"
{
	size_t writeCallback(void *data, size_t size, size_t nmemb, void *userdata)
	{
		NetworkFetcher::Response* r;
		r = static_cast<NetworkFetcher::Response*>(userdata);
		size_t sz = size * nmemb;
		std::get<2>(*r).append(QByteArray(static_cast<char*>(data), static_cast<int>(sz)));
		return (sz);
	}

	size_t headerCallback(void *data, size_t size, size_t nmemb, void *userdata)
	{
		NetworkFetcher::Response* r;
		r = reinterpret_cast<NetworkFetcher::Response*>(userdata);
		size_t _sz = size*nmemb;
		QByteArray header(static_cast<char*>(data), static_cast<int>(_sz));
		int idx = header.indexOf(':');
		if ( idx == -1)
		{
			header = header.trimmed();
			if (header.isEmpty())
			{
				return _sz;
			}
			std::get<3>(*r).append({header, "present"});
		}
		else
		{
			QByteArray key = header.left(idx).trimmed();
			QByteArray value = header.mid(idx + 1).trimmed();
			std::get<3>(*r).append({key, value});
		}
		return _sz;
	}
}

NetworkFetcher::Response NetworkFetcher::performRequest(const QUrl &url)
{
	Response ret;

	CURLcode res = CURLE_OK;
	curl_slist* headerList = nullptr;

	char* url_data = url.toString().toLatin1().data();
	setopt(curl, CURLOPT_URL, url_data);
	setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
	setopt(curl, CURLOPT_WRITEDATA, &ret);
	setopt(curl, CURLOPT_HEADERFUNCTION, headerCallback);
	setopt(curl, CURLOPT_HEADERDATA, &ret);

	for (const auto& header : info->headers)
	{
		char* hdr_str = std::get<0>(header).toLatin1().append(": ").append(std::get<1>(header)).data();
		headerList = curl_slist_append(headerList, hdr_str);
	}

	setopt(curl, CURLOPT_HTTPHEADER, headerList);
	setCurlOptions();

	res = curl_easy_perform(curl);
	qDebug() << curl_easy_strerror(res);
	if (res != CURLE_OK)
	{
		switch (res)
		{
			case CURLE_OPERATION_TIMEDOUT:
				std::get<0>(ret) = res;
				std::get<2>(ret) = "Operation Timeout.";
				break;
			case CURLE_SSL_CERTPROBLEM:
				std::get<0>(ret) = res;
				std::get<2>(ret) = curl_easy_strerror(res);
				break;
		default:
				std::get<0>(ret) = -1;
				std::get<2>(ret) = "Failed to query.";
		}
	}
	else
	{
		int32_t http_code = 0;
		getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		std::get<0>(ret) = static_cast<int32_t>(http_code);
	}

	getinfo(curl, CURLINFO_TOTAL_TIME, &info->lastRequest.totalTime);
	getinfo(curl, CURLINFO_NAMELOOKUP_TIME, &info->lastRequest.nameLookupTime);
	getinfo(curl, CURLINFO_CONNECT_TIME, info->lastRequest.connectTime);
	getinfo(curl, CURLINFO_APPCONNECT_TIME, &info->lastRequest.appConnectTime);
	getinfo(curl, CURLINFO_PRETRANSFER_TIME, &info->lastRequest.preTransferTime);
	getinfo(curl, CURLINFO_STARTTRANSFER_TIME, &info->lastRequest.startTransferTime);
	getinfo(curl, CURLINFO_REDIRECT_TIME, &info->lastRequest.redirectTime);
	getinfo(curl, CURLINFO_REDIRECT_COUNT, &info->lastRequest.redirectCount);

	curl_slist_free_all(headerList);
	curl_easy_reset(curl);

	std::get<1>(ret) = info->lastRequest.totalTime;
	return ret;

}

void NetworkFetcher::setCurlOptions()
{
	auto& auth = info->basicAuth;
	if (std::get<0>(auth).isEmpty() == false)
	{
		char* auth_str = QString("%1:%2").arg(std::get<0>(auth), std::get<1>(auth)).toLatin1().data();
		setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
		setopt(curl, CURLOPT_USERPWD, auth_str);
	}
	setopt(curl, CURLOPT_USERAGENT, getUserAgent().data());
	if (info->timeout > std::chrono::milliseconds(0))
	{
		setopt(curl, CURLOPT_TIMEOUT_MS, info->timeout.count());
		setopt(curl, CURLOPT_NOSIGNAL, 1);
	}
	else
	{
		setopt(curl, CURLOPT_TIMEOUT, 0);
		setopt(curl, CURLOPT_NOSIGNAL, 1);
	}

	if (info->followRedirects == true)
	{
		setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		setopt(curl, CURLOPT_MAXREDIRS, static_cast<int64_t>(info->maxRedirects));
	}

	if (info->noSignal)
	{
		setopt(curl, CURLOPT_NOSIGNAL, 1);
	}

	if (info->certPath.isEmpty() == false)
	{
		char* data = info->certPath.toLatin1().data();
		setopt(curl, CURLOPT_SSLCERT, data);
	}

	if (info->certType.isEmpty() == false)
	{
		char* data = info->certType.toLatin1().data();
		setopt(curl, CURLOPT_SSLCERTTYPE, data);
	}

	if ( info->keyPath.isEmpty() == false)
	{
		char* data = info->keyPath.toLatin1().data();
		setopt(curl, CURLOPT_SSLKEY, data);
	}

	if (info->keyPassword.isEmpty() == false)
	{
		char* data = info->keyPassword.toLatin1().data();
		setopt(curl, CURLOPT_KEYPASSWD, data);
	}

	if (info->uriProxy.isEmpty() == false)
	{
		char* data = info->uriProxy.toLatin1().data();
		setopt(curl, CURLOPT_PROXY, data);
		setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 1L);

		if (info->proxyAuth.isEmpty() == false)
		{
			char* data = info->proxyAuth.toLatin1().data();
			setopt(curl, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
			setopt(curl, CURLOPT_PROXYUSERPWD, data);
		}
	}

	setopt(curl, CURLOPT_NOPROGRESS, 1L);
}

void NetworkFetcher::appendContentLenght(const QNetworkRequest &request, size_t uploadSize)
{
	QList<QByteArray> raw_headers = request.rawHeaderList();
	for (const QByteArray & raw_header : raw_headers)
	{
		if (raw_header.toLower() == "content-length")
		{
			return;
		}
	}

	qulonglong sz = uploadSize;
	info->headers.push_back({"content-length", QByteArray::number(sz)});
}

QString NetworkFetcher::getUserAgent()
{
	return QString("vetclinic/0.0.1");
}

void NetworkFetcher::setRequest(const QNetworkRequest &request,
								std::chrono::milliseconds timeout,
								bool unsetExpect)
{
	info->timeout = timeout;

	QVector<Header> headers;
	QList<QByteArray> rawHeaders = request.rawHeaderList();
	for (const QByteArray & rawHeader : rawHeaders)
	{
		const QByteArray & raw_header_data = request.rawHeader(rawHeader);
		headers.push_back({rawHeader, raw_header_data});
	}

	if (unsetExpect == true)
	{
		headers.push_back({"Expect", ""});
	}

	info->headers = std::move(headers);
}
