#include "change_password_dialog.h"
#include "ui_change_password_dialog.h"

ChangePasswordDialog::ChangePasswordDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ChangePasswordDialog)
{
	ui->setupUi(this);
	ui->match_label->hide();
	ui->incorrect_label->hide();
}

ChangePasswordDialog::~ChangePasswordDialog()
{
	delete ui;
}

void ChangePasswordDialog::accept()
{
	ui->match_label->hide();
	ui->incorrect_label->hide();
	QString new1 = ui->new_lineEdit->text();
	QString new2 = ui->confirm_lineEdit->text();
	if (new1 != new2)
	{
		ui->match_label->show();
		return;
	}
	if (new1.isEmpty() == true || new2.isEmpty() == true)
	{
		ui->incorrect_label->show();
		return;
	}
	newPassword = QVariant(new1).toByteArray();
	QDialog::accept();
}

void ChangePasswordDialog::setOld(const QByteArray &value)
{
	ui->old_lineEdit->setText(QVariant(value).toString());
}

QByteArray ChangePasswordDialog::getNewPassword() const
{
    return newPassword;
}
