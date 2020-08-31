#include <QNetworkRequest>
#include <QDebug>

#include "admin_pannel.h"
#include "ui_admin_pannel.h"
#include "network/network_fetcher.h"
#include "utils/utils.h"

AdminPannel::AdminPannel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::AdminPannel()),
	model(new UsersTableModel())
{
	ui->setupUi(this);
}

bool AdminPannel::show(const QUrl &url, std::chrono::milliseconds tout, const QByteArray &pass)
{
	ui->tableView->setModel(model);
	int model_col_count = model->columnCount();
	for (int i = 0; i < model_col_count; ++i)
	{
		ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
	}

	QNetworkRequest req;
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(pass));
	req.setUrl(url);

	NetworkFetcher fetcher;
	auto reply = fetcher.httpGet(req, tout);
	if (std::get<0>(reply) != 200)
	{
		qCritical() << Q_FUNC_INFO << "Invalid data" << std::get<2>(reply);
		return  false;
	}
	else
	{
		QVector<ShortUserInfo> data = deserializeArray<ShortUserInfo>(std::get<2>(reply));
		model->setTableData(data);
	}

	return true;
}

AdminPannel::~AdminPannel()
{
	delete ui;
	delete model;
}
