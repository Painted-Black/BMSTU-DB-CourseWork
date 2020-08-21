#include <QNetworkReply>
#include "ui_animal.h"
#include "animal_edit_widget.h"
#include "types/animalstate.h"
#include "core/network/network_fetcher.h"
#include "utlis/utils.h"

AnimalEditWidget::AnimalEditWidget(QWidget *parent)
	: QWidget(parent), ui(new Ui::animal_widget())
{

}

void AnimalEditWidget::show(const QUrl& url, const QByteArray& pass)
{
	QNetworkRequest request;
	request.setUrl(url);
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(pass));

	NetworkFetcher fetcher;
	auto reply = fetcher.httpGet(request, std::chrono::milliseconds(10000));
	const auto& code = std::get<0>(reply);
	const auto& body = std::get<2>(reply);
	if (code != 200)
	{
		qCritical() << Q_FUNC_INFO << "Failed request. Http code:"<< code << body;
		return;
	}

	AnimalState state;
	state.deserialize(fromJson(body));
	int i = 0;
}
