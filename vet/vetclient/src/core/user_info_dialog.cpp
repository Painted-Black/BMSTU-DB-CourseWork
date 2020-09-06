#include "user_info_dialog.h"
#include "ui_user_info_dialog.h"
#include "change_login_dialog.h"
#include "change_password_dialog.h"
#include "chose_access_leveldialog.h"
#include "network/network_fetcher.h"
#include "utils/singlenton.h"
#include "config/config.h"
#include "popup.h"
#include "types/json_fields.h"

#include <QPushButton>
#include <QDebug>
#include <QNetworkAccessManager>

UserInfoDialog::UserInfoDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::UserInfoDialog)
{
	ui->setupUi(this);
	connect(ui->change_login_toolButton, &QPushButton::released, this, &UserInfoDialog::changeLoginBtn);
	connect(ui->calcel_pushButton, &QPushButton::released, this, &UserInfoDialog::reject);
	connect(ui->change_pass_toolButton, &QPushButton::released, this, &UserInfoDialog::changePasswordBtn);
	connect(ui->change_level_toolButton, &QPushButton::released, this, &UserInfoDialog::changeAccessLevel);
	connect(ui->save_pushButton, &QPushButton::released, this, &UserInfoDialog::save);
}

UserInfoDialog::~UserInfoDialog()
{
	delete ui;
}

void UserInfoDialog::show(ShortUserInfo info)
{
	mData = info;
	ui->surname_lineEdit->setText(mData.getSurname());
	ui->name_lineEdit->setText(mData.getName());
	ui->patr_lineEdit->setText(mData.getPatronymic());
	ui->login_lineEdit->setText(mData.getLogin());
	ui->access_level_comboBox->addItem(mData.getAccessLevel());
	ui->empl_dateEdit->setDate(mData.getEmployDate());
	ui->pos_titile_lineEdit->setText(mData.getPositionTitle());
	ui->pass_lineEdit->setText(QString(mData.getPassword()));

	QDate fire_date = mData.getFireDate();
	if (fire_date.isValid() == false)
	{
		ui->fire_label->hide();
		ui->fire_dateEdit->hide();
	}
	else
	{
		ui->fire_dateEdit->setDate(fire_date);
	}
}

ShortUserInfo UserInfoDialog::getShortUserInfo()
{
	return mData;
}

void UserInfoDialog::setPassword(const QByteArray &value)
{
	password = value;
}

QByteArray UserInfoDialog::serializeAccessData()
{
	QJsonObject root_obj;
	root_obj.insert(AccessJson::field_acc_id, QJsonValue::fromVariant(QVariant::fromValue(mData.getUid())));
	if (passChanged)
	{
		root_obj.insert(AccessJson::field_acc_password, QJsonValue::fromVariant(QVariant(newPassword)));
	}
	if (loginChanged)
	{
		root_obj.insert(AccessJson::field_acc_login, QJsonValue(newLogin));
	}
	if (lvlChanged)
	{
		root_obj.insert(AccessJson::field_acc_access_level, QJsonValue(newAccessLevel));
	}
	return QJsonDocument(root_obj).toJson();
}

QString UserInfoDialog::getNewAccessLevel() const
{
	return newAccessLevel;
}

QByteArray UserInfoDialog::getNewPassword() const
{
	return newPassword;
}

QString UserInfoDialog::getNewLogin() const
{
	return newLogin;
}

ShortUserInfo UserInfoDialog::getNewAccessData() const
{
	return mData;
}

bool UserInfoDialog::getLvlChanged() const
{
	return lvlChanged;
}

bool UserInfoDialog::isChanged() const
{
	return (passChanged || loginChanged || lvlChanged);
}

bool UserInfoDialog::getPassChanged() const
{
    return passChanged;
}

bool UserInfoDialog::getLoginChanged() const
{
    return loginChanged;
}

void UserInfoDialog::changeLoginBtn()
{
    qDebug() << Q_FUNC_INFO << "Change login";
	ChangeLoginDialog* dia = new ChangeLoginDialog(this);
	dia->setOldLogin(mData.getLogin());
	if (dia->exec() == QDialog::Accepted)
	{
		newLogin = dia->getNewLogin();
		loginChanged = true;
		mData.setLogin(newLogin);
		ui->login_lineEdit->setText(newLogin);
//		qDebug() << newLogin;
	}
}

void UserInfoDialog::changePasswordBtn()
{
	qDebug() << Q_FUNC_INFO << "Change password";

	ChangePasswordDialog* dia = new ChangePasswordDialog(this);
	dia->setOld(mData.getPassword());
	if (dia->exec() == QDialog::Accepted)
	{
		newPassword = dia->getNewPassword();
		passChanged = true;
		mData.setPassword(newPassword);
		ui->pass_lineEdit->setText(newPassword);
//		qDebug() << newPassword;
	}
}

void UserInfoDialog::changeAccessLevel()
{
	qDebug() << Q_FUNC_INFO << "Change access level";

	ChoseAccessLevelDialog* dia = new ChoseAccessLevelDialog(this);
	dia->setOldAccesslevel(mData.getAccessLevel());
	if (dia->exec() == QDialog::Accepted)
	{
		newAccessLevel = dia->getAccessLevel();
		lvlChanged = true;
		mData.setAccessLevel(newAccessLevel);
		ui->access_level_comboBox->clear();
		ui->access_level_comboBox->addItem(newAccessLevel);
//		qDebug() << newAccessLevel;
	}
}

void UserInfoDialog::save()
{
	qDebug() << "Saving";
	if (lvlChanged || passChanged || loginChanged)
	{
		qDebug() << "Have changes...";
		auto& cfg = Singlenton<Config>::getInstance();
		QNetworkRequest request(cfg.getUrlUpdateUser());
		request.setRawHeader("Authorization", QByteArray("Explicit: ").append(password));
		request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
		NetworkFetcher fetcher;

		QByteArray raw_data = serializeAccessData();

		auto reply = fetcher.httpPost(request, raw_data, cfg.getTimeout());
		int32_t code = std::get<0>(reply);
		auto& popup = Singlenton<PopUp>::getInstance();
		if (code == -1)
		{
			popup.setPopupText("Нет соединения с интернетом или доступа к серверу.");
			popup.show();
			return;
		}
		if (code != 200)
		{
			popup.setPopupText("Возникла ошибка.");
			popup.show();
			return;
		}
		//ok
		popup.setPopupText("Данные успешно обновлены.");
		popup.show();
	}
	else
	{
		qDebug() << "No changes.";
	}
	QDialog::accept();
}
