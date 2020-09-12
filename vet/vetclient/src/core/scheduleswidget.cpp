#include "scheduleswidget.h"
#include "ui_scheduleswidget.h"
#include "types/shedules_short_info.h"
#include "network/network_fetcher.h"
#include "utils/singlenton.h"
#include "core/popup.h"
#include "config/config.h"
#include "utils/utils.h"

#include <QNetworkRequest>

SchedulesWidget::SchedulesWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SchedulesWidget),
	model(new SchedulesTableModel())
{
	ui->setupUi(this);
	ui->tableView->setModel(model);
	int model_col_count = model->columnCount();
	for (int i = 0; i < model_col_count; ++i)
	{
		ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
		ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	}
}

SchedulesWidget::~SchedulesWidget()
{
	delete ui;
}

void SchedulesWidget::init()
{
	QVector<ShedulesShortInfo> vec;

	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest request;
	request.setUrl(cfg.getUrlAllSchedules());
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(mPassword));

	NetworkFetcher fetcher;
	auto reply = fetcher.httpGet(request, cfg.getTimeout());
	const auto& code = std::get<0>(reply);
	const auto& body = std::get<2>(reply);
	if (code != 200)
	{
		qCritical() << Q_FUNC_INFO << "Failed request. Http code:"<< code << body;
		return;
	}
	else
	{
		vec = deserializeArray<ShedulesShortInfo>(body);
	}

	model->setTableData(vec);
}

void SchedulesWidget::setPassword(const QByteArray &password)
{
	mPassword = password;
}
