#include "main_vet_pannel.h"
#include "ui_main_vet_pannel.h"
#include "network/network_fetcher.h"
#include "types/position.h"
#include "utils/singlenton.h"
#include "config/config.h"
#include "utils/utils.h"
#include "core/position_info_dialog.h"

#include <QNetworkRequest>
#include <QDebug>

MainVetPannel::MainVetPannel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainVetPannel),
	model(new PositionsTableModel())
{
	ui->setupUi(this);
	connect(ui->tableView, &QAbstractItemView::doubleClicked, this, &MainVetPannel::tableViewDoubleClicked);
}

MainVetPannel::~MainVetPannel()
{
	delete ui;
}

void MainVetPannel::update()
{
	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest req;
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(password));
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	req.setUrl(cfg.getUrlAllPositions());

	NetworkFetcher fetcher;
	auto reply = fetcher.httpGet(req, cfg.getTimeout());
	if (std::get<0>(reply) != 200)
	{
		qCritical() << Q_FUNC_INFO << "Invalid data" << std::get<2>(reply);
	}
	else
	{
		QVector<Position> pos_info = deserializeArray<Position>(std::get<2>(reply));
		model->setTableData(pos_info);
	}

	ui->tableView->setModel(model);
	int model_col_count = model->columnCount();
	for (int i = 0; i < model_col_count; ++i)
	{
		ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
	}
}

void MainVetPannel::setPassword(const QByteArray &pass)
{
	password = pass;
}

void MainVetPannel::tableViewDoubleClicked(const QModelIndex &index)
{
	qDebug() << "Position double clicked" << " row: " << index.row();

	qDebug() << Q_FUNC_INFO << "Double click";
	PositionInfoDialog* dialog = new PositionInfoDialog(this);
	dialog->setPassword(password);
	dialog->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
	dialog->show(model->dataAt(index.row()));
	if (dialog->exec() == QDialog::Accepted)
	{
		if (dialog->isChanged())
		{
			Position new_pos = dialog->getNewPosition();
			model->setDataAt(index.row(), new_pos);
		}
		qDebug() << "Updating table";
	}

}
