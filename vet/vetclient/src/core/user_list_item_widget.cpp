#include "user_list_item_widget.h"
#include "ui_user_list_item_widget.h"
#include "network/network_fetcher.h"
#include "utils/utils.h"

#include <QNetworkRequest>
#include <QDebug>

UserListItemWidget::UserListItemWidget(QWidget *parent) :
	QWidget(parent)
{
	view = new QListWidget(this);
	QHBoxLayout* lay = new QHBoxLayout(this);
	lay->addWidget(view);
	setLayout(lay);

	connect(view, &QListWidget::itemDoubleClicked, this, &UserListItemWidget::selectItemWidget);
}

bool UserListItemWidget::show(const QUrl &url, std::chrono::milliseconds tout, const QByteArray &pass)
{
	QNetworkRequest req;
	req.setUrl(url);
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(pass));

	NetworkFetcher fetcher;
	auto reply = fetcher.httpGet(req, tout);
	if (std::get<0>(reply) != 200)
	{
		qCritical() << Q_FUNC_INFO << "Invalid data" << std::get<2>(reply);
		return  false;
	}
	else
	{
		mData = deserializeArray<ShortStaffInfo>(std::get<2>(reply));
		for (const auto& v : mData)
		{
			QListWidgetItem* item = new QListWidgetItem(view);
			view->addItem(item);
			QWidget* inserted_widget = addWidget(v);
			inserted_widget->setProperty("UID", QVariant::fromValue(v.getUid()));
			item->setSizeHint(inserted_widget->sizeHint());
			view->setItemWidget(item, inserted_widget);
		}
	}
	return true;
}

ShortStaffInfo UserListItemWidget::findById(uint64_t id)
{
	ShortStaffInfo cur;
	for (int i = 0; i < mData.size(); ++i)
	{
		cur = mData.at(i);
		if (cur.getUid() == id)
			return cur;
	}
	return  cur;
}

ShortStaffInfo UserListItemWidget::dataAt(int i)
{
	return mData.at(i);
}

QWidget *UserListItemWidget::addWidget(const ShortStaffInfo &info)
{
	QWidget* form = new QWidget();
	Ui::UserListItemWidget* ui = new Ui::UserListItemWidget();
	ui->setupUi(form);
	ui->input_fio_label->setText(info.getFio());
	ui->input_pos_label->setText(info.getPosition());
	return form;
}

void UserListItemWidget::selectItemWidget(QListWidgetItem *item)
{
	uint64_t uid =view->itemWidget(item)->property("UID").value<uint64_t>();
	Q_EMIT selectItem(uid);
}
