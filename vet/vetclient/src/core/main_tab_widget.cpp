#include "main_tab_widget.h"
#include "ui_main_tab_widget.h"
#include "config/config.h"
#include "utils/singlenton.h"
#include "network/network_fetcher.h"
#include "utils/utils.h"
#include "types/sheduled_visits.h"

#include <QDebug>
#include <QIcon>
#include <QNetworkRequest>
#include <QFormLayout>

MainTabWidget::MainTabWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainTabWidget)
{
	ui->setupUi(this);
	connect(ui->new_visit_pushButton, &QPushButton::released, this, &MainTabWidget::new_visit_btn_pressed);
	connect(ui->patients_pushButton, &QPushButton::released, this, &MainTabWidget::patientsBtnPressed);
}

MainTabWidget::~MainTabWidget()
{
	delete ui;
}

void MainTabWidget::new_visit_btn_pressed()
{
	emit newVisit();
}

void MainTabWidget::patientsBtnPressed()
{
	emit patients();
}

void MainTabWidget::setAccessData(const AccessData &acc_data)
{
	access_data = acc_data;
}

bool MainTabWidget::show(const QUrl &url, std::chrono::milliseconds tout, const QByteArray &pass)
{
	QNetworkRequest request;
	request.setUrl(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(pass));
	QByteArray data = serializeCurrentDate();
	NetworkFetcher fetcher;
	auto reply = fetcher.httpPost(request, data, tout);
//	auto reply = fetcher.httpGet(request, tout);
	const auto& code = std::get<0>(reply);
	const auto& body = std::get<2>(reply);
	if (code != 200)
	{
		qCritical() << Q_FUNC_INFO << "Failed request. Http code:" << code << body;
		return false;
	}

	QVector<SheduledVisits> visits_info = deserializeArray<SheduledVisits>(body);
	QFormLayout* lay = new QFormLayout(this);
	if (visits_info.isEmpty() == true)
	{
		QLabel* label = new QLabel("Запланированных осмотров нет");
		QFont font = label->font();
		font.setPointSize(16);
		label->setFont(font);
		lay->addWidget(label);
	}
	else
	{
		for (const auto& v : visits_info)
		{
			QLabel* name = new QLabel(this);
			QLabel* spec = new QLabel(this);
			QFont font = name->font();
			font.setPointSize(16);
			name->setFont(font);
			spec->setFont(font);
			name->setText(v.getAnimalName() + ", ");
			spec->setText(v.getAnimalSpecies());
			lay->addRow(name, spec);
		}
	}
	QWidget* widget = new QWidget(this);
	widget->setLayout(lay);
	ui->scrollArea->setWidget(widget);
	return true;
}

QByteArray MainTabWidget::serializeCurrentDate()
{
	QDate current = QDate::currentDate();
	QString current_date = current.toString(Qt::ISODate);
	QJsonObject obj;
	obj.insert("date", current_date);
	return QJsonDocument(obj).toJson();
}
