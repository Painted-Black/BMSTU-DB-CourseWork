#include "position_info_dialog.h"
#include "ui_position_info_dialog.h"
#include "utils/singlenton.h"
#include "popup.h"
#include "config/config.h"
#include "network/network_fetcher.h"
#include "utils/utils.h"

#include <QNetworkRequest>

PositionInfoDialog::PositionInfoDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PositionInfoDialog)
{
	ui->setupUi(this);
	connect(ui->cancel_pushButton, &QPushButton::released, this, &QDialog::reject);
	connect(ui->save_pushButton, &QPushButton::released, this, &PositionInfoDialog::save);
}

PositionInfoDialog::~PositionInfoDialog()
{
	delete ui;
}

void PositionInfoDialog::show(const Position &pos)
{
	old_position = pos;
	ui->title_lineEdit->setText(old_position.getTitle());
	ui->salary_spinBox->setValue(old_position.getSalary());
}

bool PositionInfoDialog::isChanged() const
{
	return mIsChanged;
}

Position PositionInfoDialog::getNewPosition()
{
	return new_position;
}

void PositionInfoDialog::save()
{
	qDebug() << "saving";

	new_position.setTitle(ui->title_lineEdit->text());
	new_position.setSalary(ui->salary_spinBox->value());
	new_position.setId(old_position.getId());
	if (new_position == old_position)
	{
		mIsChanged = false;
		QDialog::accept();
	}
	mIsChanged = true;

	//query

	bool is_ok = queryToServer();
	if (is_ok == false)
	{
		return;
	}
	QDialog::accept();
}

bool PositionInfoDialog::queryToServer()
{
	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest request(cfg.getUrlUpdatePosition());
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(password));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	NetworkFetcher fetcher;

	QByteArray raw_data = toJson(new_position.serialize());

	auto reply = fetcher.httpPost(request, raw_data, cfg.getTimeout());
	int32_t code = std::get<0>(reply);
	auto& popup = Singlenton<PopUp>::getInstance();
	if (code == -1)
	{
		popup.setPopupText("Нет соединения с интернетом или доступа к серверу.");
		popup.show();
		return false;
	}
	if (code != 200)
	{
		popup.setPopupText("Возникла ошибка.");
		popup.show();
		return false;
	}
	// ok
	qDebug() << Q_FUNC_INFO << "Saved";
	popup.setPopupText("Данные успешно сохранены.");
	popup.show();

	return true;
}

void PositionInfoDialog::setPassword(const QByteArray &value)
{
	password = value;
}
