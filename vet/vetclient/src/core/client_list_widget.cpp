#include <QDialogButtonBox>
#include <QScrollArea>
#include <QGuiApplication>
#include <QScreen>
#include "ui_clent_list_item.h"
#include "client_list_widget.h"
#include "ui_client_item_widget.h"
#include "utils/utils.h"

ClientListWidget::ClientListWidget(QWidget *parent) :
	QDialog(parent), ui(new Ui::ClientListWidget())
{
	ui->setupUi(this);
	QRect rect = QGuiApplication::screens().first()->geometry();
	centredWidget(this, rect);

	qRegisterMetaType<ShortInfoClient>();

	connect(ui->item_list, &QListWidget::doubleClicked, this, [&](const QModelIndex& idx)
	{
		selected_row_buffer = idx.row();
		accept();
	});
}

void ClientListWidget::setData(QVector<ShortInfoClient> &&data)
{
	clients = std::move(data);
}

void ClientListWidget::update()
{
	ui->item_list->clear();
	for (const auto& v : clients)
	{
		QListWidgetItem* item = new QListWidgetItem(ui->item_list);
		ui->item_list->addItem(item);
		QWidget* inserted_widget = addWidget(v);
		item->setSizeHint(inserted_widget->sizeHint());
		ui->item_list->setItemWidget(item, inserted_widget);
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

