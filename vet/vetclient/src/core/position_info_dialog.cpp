#include "position_info_dialog.h"
#include "ui_position_info_dialog.h"
#include "utils/singlenton.h"
#include "popup.h"
#include "config/config.h"
#include "network/network_fetcher.h"
#include "utils/utils.h"

#include <QNetworkRequest>

PositionInfoDialog::PositionInfoDialog(DialogType type, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PositionInfoDialog)
{
	ui->setupUi(this);
	connect(ui->cancel_pushButton, &QPushButton::released, this, &QDialog::reject);
	mType = type;
	hideErrorLabels();

	if (mType == EDIT)
	{
		connect(ui->save_pushButton, &QPushButton::released, this, &PositionInfoDialog::update);
		setWindowTitle("Редактирование должности");
		ui->save_pushButton->setText("Сохранить изменения");
	}
	else if (mType == ADD)
	{
		connect(ui->save_pushButton, &QPushButton::released, this, &PositionInfoDialog::save);
		setWindowTitle("Новая должность");
		ui->save_pushButton->setText("Сохранить");
	}
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

void PositionInfoDialog::update()
{
	qDebug() << "saving";

	new_position.setTitle(ui->title_lineEdit->text());
	new_position.setSalary(ui->salary_spinBox->value());
	new_position.setId(old_position.getId());
	if (new_position == old_position)
	{
		mIsChanged = false;
		QDialog::accept();
		return;
	}
	mIsChanged = true;
	//query

	bool is_ok = queryToServerUpdate();
	if (is_ok == false)
	{
		return;
	}
	QDialog::accept();
}

void PositionInfoDialog::save()
{
	hideErrorLabels();
	QString title = ui->title_lineEdit->text();
	int64_t salary = ui->salary_spinBox->value();
	if (title.isEmpty())
	{
		ui->error_label->show();
		return;
	}
	if (salary <= 0)
	{
		ui->error_label->show();
		return;
	}

	added_position.setTitle(title);
	added_position.setSalary(salary);

	bool is_ok = queryToServerAdd(added_position);
	if (is_ok == false)
	{
		return;
	}
	QDialog::accept();
}

bool PositionInfoDialog::queryToServerUpdate()
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

bool PositionInfoDialog::queryToServerAdd(Position pos)
{
	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest request(cfg.getUrlAddPosition());
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(password));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	NetworkFetcher fetcher;

	QByteArray raw_data = toJson(pos.serialize());

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

void PositionInfoDialog::hideErrorLabels()
{
	ui->error_label->hide();
}

void PositionInfoDialog::setPassword(const QByteArray &value)
{
	password = value;
}

Position PositionInfoDialog::getAddedPosition()
{
	return added_position;
}
