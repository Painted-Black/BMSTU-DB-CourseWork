#include "visits_widget.h"
#include "ui_visits_widget.h"
#include "ui_visit_list_item_widget.h"
#include "utils/singlenton.h"
#include "utils/utils.h"
#include "config/config.h"
#include "network/network_fetcher.h"
#include "core/new_visit_widget.h"
#include "core/popup.h"
#include "core/scroll_dialog.h"

#include <QBoxLayout>
#include <QNetworkRequest>

VisitsWidget::VisitsWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::visits_widget)
{
	ui->setupUi(this);
	connect(ui->items, &QListWidget::doubleClicked, this, &VisitsWidget::selectItemWidget);
}

VisitsWidget::~VisitsWidget()
{
	delete ui;
}

void VisitsWidget::setPassword(const QByteArray &password)
{
	mPassword = password;
}

void VisitsWidget::show()
{
	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest req;
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(mPassword));
	req.setUrl(cfg.getUrlAllVisitsShort());

	NetworkFetcher fetcher;
	auto reply = fetcher.httpGet(req, cfg.getTimeout());
	auto code = std::get<0>(reply);
	const auto& body = std::get<2>(reply);
	if (code != 200)
	{
		qCritical() << Q_FUNC_INFO << "Invalid data" << body;

		auto& popup = Singlenton<PopUp>::getInstance();
		popup.setPopupText("Произошла ошибка");
		popup.show();
	}
	else
	{
		mData = deserializeArray<ShortVisitInfo>(body);
		for (const auto& data : mData)
		{
			addItem(data);
		}
	}
}

void VisitsWidget::addItem(const ShortVisitInfo& d)
{
	QListWidgetItem* item = new QListWidgetItem(ui->items);
	ui->items->addItem(item);

	QWidget* inserted_widget = new QWidget();
	Ui::VisitListItemWidget* ui_item = new Ui::VisitListItemWidget();
	ui_item->setupUi(inserted_widget);
	ui_item->input_date_label->setText(d.visitDate().toString());
	ui_item->input_spec_label->setText(d.animalSpecies());
	ui_item->inpur_animal_label->setText(d.animalName());
	ui_item->input_doctor_label->setText(d.docFio());

	item->setSizeHint(inserted_widget->sizeHint());
	ui->items->setItemWidget(item, inserted_widget);

}

void VisitsWidget::selectItemWidget(const QModelIndex& row)
{
	qDebug() << Q_FUNC_INFO << "row: " << row.row();
	bool is_ok;
	Visit vis = queryToServer(mData.at(row.row()).visitId(), &is_ok);
	if (!is_ok)
	{
		return;
	}
	NewVisitWidget * wdg = new NewVisitWidget(NewVisitWidget::SHOW);
	ScrollDialog* d = new ScrollDialog(this);
	wdg->setPassword(mPassword);
	wdg->setVisitShow(vis);
	wdg->show();
	d->setWidget(wdg);
	d->exec();
}

Visit VisitsWidget::queryToServer(uint64_t vis_id, bool* is_ok)
{
	Visit vis;
	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest req;
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(mPassword));
	QUrl url = cfg.getUrlVisitFull();
	url.setQuery(QString("id=%1").arg(vis_id));
	req.setUrl(url);

	NetworkFetcher fetcher;
	auto reply = fetcher.httpGet(req, cfg.getTimeout());
	auto code = std::get<0>(reply);
	const auto& body = std::get<2>(reply);
	if (code != 200)
	{
		qCritical() << Q_FUNC_INFO << "Invalid data" << body;
		auto& popup = Singlenton<PopUp>::getInstance();
		popup.setPopupText("Произошла ошибка");
		popup.show();
		*is_ok = false;
	}
	else
	{
		*is_ok = true;
		vis.deserialize(fromJson(body));
	}
	return vis;
}
