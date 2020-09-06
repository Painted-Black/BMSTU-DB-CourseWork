#include "staff_tab_widget.h"
#include "ui_staff_tab_widget.h"
#include "utils/singlenton.h"
#include "core/popup.h"
#include "network/network_fetcher.h"
#include "config/config.h"
#include "utils/utils.h"

#include <QNetworkAccessManager>
#include <QDebug>
#include <QPushButton>

StaffTabWidget::StaffTabWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::StaffTabWidget),
	model(new StaffTableModel())
{
	ui->setupUi(this);

	connect(ui->add_staff_toolButton, &QPushButton::released, this, &StaffTabWidget::addStaffBtn);
	connect(ui->delete_staff_toolButton, &QPushButton::released, this, &StaffTabWidget::removeStaffBtn);
}

StaffTabWidget::~StaffTabWidget()
{
	delete ui;
}

void StaffTabWidget::setPassword(const QByteArray &password)
{
	mPassword = password;
}

void StaffTabWidget::update()
{
	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest req;
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(mPassword));
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	req.setUrl(cfg.getUrlStaffFullInfo());

	NetworkFetcher fetcher;
	auto reply = fetcher.httpGet(req, cfg.getTimeout());
	auto code = std::get<0>(reply);
	const auto& body = std::get<2>(reply);
	if (code != 200)
	{
		qCritical() << Q_FUNC_INFO << "Invalid data" << body;
	}
	else
	{
		QVector<Staff> staff_info = deserializeArray<Staff>(body);
		model->setTableData(staff_info);
	}

	ui->tableView->setModel(model);
	int model_col_count = model->columnCount();
	for (int i = 0; i < model_col_count; ++i)
	{
		ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
	}
}

void StaffTabWidget::addStaffBtn()
{
	qDebug() << Q_FUNC_INFO << "Add staff";
}

void StaffTabWidget::removeStaffBtn()
{
	qDebug() << Q_FUNC_INFO << "Remove staff";
}
