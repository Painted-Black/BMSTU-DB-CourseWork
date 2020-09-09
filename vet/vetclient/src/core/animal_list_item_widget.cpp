#include <QNetworkReply>
#include <QVariant>
#include "utils/utils.h"
#include "ui_animal_list_item_widget.h"
#include "animal_list_item_widget.h"
#include "core/network/network_fetcher.h"
#include "types/image_loader.h"

AnimalListWidget::AnimalListWidget(QWidget * parent)
	: QWidget(parent)
{
	view = new QListWidget(this);
	QHBoxLayout* lay = new QHBoxLayout(this);
	lay->addWidget(view);
	setLayout(lay);

	connect(view, &QListWidget::itemDoubleClicked, this, &AnimalListWidget::selectItemWidget);
}

bool AnimalListWidget::show(const QUrl& url,
							std::chrono::milliseconds tout, const QByteArray &data)
{
	QNetworkRequest req;
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(data));
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
		auto animals_info = deserializeArray<ShortAnimalInfo>(std::get<2>(reply));
		for (const auto& v : animals_info)
		{
			addAnimal(v, data);
		}
	}
	return true;
}

void AnimalListWidget::addAnimal(const ShortAnimalInfo &info, const QByteArray& key)
{
	addWidget(info, key);
}

void AnimalListWidget::addWidget(const ShortAnimalInfo & info, const QByteArray& key)
{
	QListWidgetItem* item = new QListWidgetItem(view);
	view->addItem(item);

	QWidget* inserted_widget = new QWidget();
	Ui::Form* ui = new Ui::Form();
	ui->setupUi(inserted_widget);
	ui->input_name->setText(info.getName());
	ui->input_spec->setText(info.getSpec());
	ui->input_birth->setText(info.getBirth().toString(Qt::SystemLocaleLongDate));

	QPixmap img = ImageLoader::getInstance().loadPixmap(info.getRelativeToFilePath(), key);
	ui->photo_label->setPixmap(img.scaled(ui->photo_label->size()));

	inserted_widget->setProperty("UID", QVariant::fromValue(info.getUid()));
	item->setSizeHint(inserted_widget->sizeHint());
	view->setItemWidget(item, inserted_widget);
}

void AnimalListWidget::selectItemWidget(QListWidgetItem * item)
{
	uint64_t uid =view->itemWidget(item)->property("UID").value<uint64_t>();
	Q_EMIT selectItem(uid);
}
