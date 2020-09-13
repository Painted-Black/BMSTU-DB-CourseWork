#include "add_user_dialog.h"
#include "ui_add_user_dialog.h"
#include "types/json_fields.h"
#include "types/user_data.h"
#include "chose_staff_dialog.h"
#include "utils/singlenton.h"
#include "config/config.h"
#include "utils/utils.h"
#include "network/network_fetcher.h"

#include <QNetworkAccessManager>

AddUserDialog::AddUserDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddUserDialog)
{
	ui->setupUi(this);
	ui->access_level_comboBox->addItem(AccessLevelType::access_vet);
	ui->access_level_comboBox->addItem(AccessLevelType::access_main);
	ui->access_level_comboBox->addItem(AccessLevelType::access_admin);
	ui->access_level_comboBox->addItem(AccessLevelType::access_registry);
	hideErrorMessages();
	connect(ui->staff_pushButton, &QPushButton::released, this, &AddUserDialog::choseStaff);
}

AddUserDialog::~AddUserDialog()
{
	delete ui;
}

void AddUserDialog::accept()
{
	hideErrorMessages();
	if (staff_id == -1)
	{
		ui->staff_label->show();
		return;
	}
	login = ui->login_lineEdit->text();
	if (login.isEmpty() == true)
	{
		ui->incorrect_login_label->show();
		return;
	}
	QString pass1, pass2;
	pass1 = ui->pass_lineEdit->text();
	pass2 = ui->confirm_pass_lineEdit->text();
	if (pass1 != pass2)
	{
		ui->diff_label->show();
		return;
	}
	if (pass1.isEmpty() || pass2.isEmpty())
	{
		ui->incorrect_label->show();
		return;
	}

	data.setLogin(login);

	acc_lvl = ui->access_level_comboBox->currentText();
	AccessLevel level;
	level.fromString(acc_lvl);
	data.setLevel(level);

	Staff s;
	s.setId(staff_id);
	data.setOwner(s);
	password = QVariant(pass1).toByteArray();
	data.setPassword(password);

	bool is_ok = queryToServer();
	if (is_ok == true)
	{
		QDialog::accept();
	}
	else
	{
		auto& popup = Singlenton<PopUp>::getInstance();
		popup.setPopupText("Произошла ошибка, попробуйте еще раз.");
		popup.show();
	}
}

void AddUserDialog::hideErrorMessages()
{
	ui->incorrect_label->hide();
	ui->diff_label->hide();
	ui->incorrect_login_label->hide();
	ui->staff_label->hide();
}

void AddUserDialog::choseStaff()
{
	qDebug() << "chosing staff";
	ChoseStaffDialog chose_dialog(this);
	chose_dialog.setAccessData(access_data);
	chose_dialog.show();
	if (chose_dialog.exec() == QDialog::Rejected)
	{
		return;
	}
	info = chose_dialog.getStaffIinfo();
	staff_id = info.getUid();
	ui->surname_lineEdit->setText(info.getFio());
	ui->pos_lineEdit->setText(info.getPosition());
}

bool AddUserDialog::queryToServer()
{
	qDebug() << Q_FUNC_INFO << "Query";

	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest request(cfg.getUrlAddUser());
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(access_data));
	NetworkFetcher fetcher;

	QByteArray raw_data = accessSerialize(data);

	auto reply = fetcher.httpPost(request, raw_data, cfg.getTimeout());
	int32_t code = std::get<0>(reply);
	auto& popup = Singlenton<PopUp>::getInstance();
	if (code == -1)
	{
		popup.setPopupText("Нет соединения с интернетом или доступа к серверу.");
		popup.show();
		return false;
	}
	if (code != 201)
	{
		popup.setPopupText("Возникла ошибка.");
		popup.show();
		return false;
	}
	// ok
	qDebug() << Q_FUNC_INFO << "Saved";
	popup.setPopupText("Данные осмотра успешно сохранены.");
	popup.show();

	return true;
}

AccessData AddUserDialog::getNewAccessData() const
{
	return data;
}

ShortStaffInfo AddUserDialog::getNewStaffAccountData() const
{
	return info;
}

bool AddUserDialog::getIsSuccess() const
{
	return isSuccess;
}

void AddUserDialog::setAccessData(const QByteArray &value)
{
	access_data = value;
}


