#include <QDialogButtonBox>
#include <QScrollArea>
#include <QGuiApplication>
#include <QScreen>
#include "network/network_fetcher.h"
#include "ui_client_widget_list.h"
#include "client_list_widget.h"
#include "ui_client_item_widget.h"
#include "utils/utils.h"

ClientListWidget::ClientListWidget(QWidget *parent) :
	QWidget(parent), ui(new Ui::ClientWidgetList())
{
	ui->setupUi(this);
	QRect rect = QGuiApplication::screens().first()->geometry();
	centredWidget(this, rect);

	qRegisterMetaType<ShortInfoClient>();

	connect(ui->listWidget, &QListWidget::doubleClicked, this, [&](const QModelIndex& idx)
	{
		selected_row_buffer = idx.row();
		Q_EMIT selectClient(selected_row_buffer);
	});
}

std::tuple<bool, QString> ClientListWidget::requestData(const QUrl& url,
								   std::chrono::milliseconds tout,
								   const QByteArray& pass)
{
	NetworkFetcher fetcher;
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(pass));

	auto answer = fetcher.httpGet(request, tout);
	auto code = std::get<0>(answer);
	if (code == -1)
	{
		return { false, "Отсутствует подключение к интернету или нет доступа к серверу."};
	}
	else if (code != 200)
	{
		return { false, "Произошла ошибка, проверьте данные"};
	}

	clients = deserializeArray<ShortInfoClient>(std::get<2>(answer));
	return { true, "" };
}

void ClientListWidget::setData(QVector<ShortInfoClient> &&data)
{
	clients = std::move(data);
}

void ClientListWidget::update()
{
	ui->listWidget->clear();
	for (const auto& v : clients)
	{
		QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
		ui->listWidget->addItem(item);
		QWidget* inserted_widget = addWidget(v);
		item->setSizeHint(inserted_widget->sizeHint());
		ui->listWidget->setItemWidget(item, inserted_widget);
	}
}

const ShortInfoClient &ClientListWidget::getSelectedClient() const
{
	return clients[selected_row_buffer];
}

QWidget* ClientListWidget::addWidget(const ShortInfoClient & info)
{
	QWidget* form = new QWidget();
	auto ui = new Ui::ClientItemWidget();
	ui->setupUi(form);
	ui->input_surname->setText(info.surname);
	ui->input_name->setText(info.name);
	ui->input_patronymic->setText(info.patronymic);
	ui->input_birthday->setText(info.birthday.toString(Qt::SystemLocaleLongDate));
	return form;
}

