#include <QNetworkReply>
#include "utlis/utils.h"
#include "ui_animal_list_item_widget.h"
#include "animal_list_item_widget.h"

AnimalListWidget::AnimalListWidget(QWidget * parent)
	: QWidget(parent)
{
	view = new QListView(this);
	view->setSelectionMode(QAbstractItemView::SingleSelection);
	view->setDragEnabled(true);
	view->setAcceptDrops(true);
	view->setDropIndicatorShown(true);
	model = new AnimalListModel();
	delegate = new AnimalListDelegate(this);
	delegate->setModelData(this, model, QModelIndex());
	view->setModel(model);
	view->setItemDelegate(delegate);

	QHBoxLayout* lay = new QHBoxLayout(this);
	lay->addWidget(view);
	setLayout(lay);

	manager = new QNetworkAccessManager();
	connect(manager, &QNetworkAccessManager::finished, this, &AnimalListWidget::response);
}

void AnimalListWidget::show(const QUrl& url, const QByteArray &data)
{
	QNetworkRequest req;
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(data));
	req.setUrl(url);
	manager->get(req);
}

void AnimalListWidget::response(QNetworkReply * rep)
{
	uint32_t code = rep->attribute(QNetworkRequest::HttpStatusCodeAttribute).toUInt();
	if (code == true)
	{
		Q_EMIT interruptRequestData();
	}
	else
	{
		auto arr_info = deserializeArray<ShortAnimalInfo>(rep->readAll());
		model->setAnimalsInfo(std::move(arr_info));
		view->reset();
	}
}
