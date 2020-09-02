#include "user_info_dialog.h"
#include "ui_user_info_dialog.h"
#include "change_login_dialog.h"
#include "change_password_dialog.h"
#include "chose_access_leveldialog.h"

#include <QPushButton>
#include <QDebug>

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

bool UserInfoDialog::isChanged()
{
	return changed;
}

ShortUserInfo UserInfoDialog::getShortUserInfo()
{
	return mData;
}

void UserInfoDialog::changeLoginBtn()
{
	qDebug() << Q_FUNC_INFO << "Change login";
	ChangeLoginDialog* dia = new ChangeLoginDialog(this);
	dia->setOldLogin(mData.getLogin());
	if (dia->exec() == QDialog::Accepted)
	{
		newLogin = dia->getNewLogin();
		changed = true;
		mData.setLogin(newLogin);
		qDebug() << newLogin;
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
		changed = true;
		mData.setPassword(newPassword);
		qDebug() << newPassword;
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
		changed = true;
		mData.setAccessLevel(newAccessLevel);
		qDebug() << newAccessLevel;
	}
}

void UserInfoDialog::save()
{
	QDialog::accept();
}
