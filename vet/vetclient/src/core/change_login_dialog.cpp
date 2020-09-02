#include "change_login_dialog.h"
#include "ui_change_login_dialog.h"

ChangeLoginDialog::ChangeLoginDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ChangeLoginDialog)
{
	ui->setupUi(this);
	ui->empty_label->hide();
	ui->busy_label->hide();
}

void ChangeLoginDialog::setOldLogin(const QString &old)
{
	ui->input_old_label->setText(old);
}

void ChangeLoginDialog::accept()
{
	ui->empty_label->hide();
	ui->busy_label->hide();
	new_login = ui->new_lineEdit->text();
	if (new_login.isEmpty() == true)
	{
		ui->empty_label->show();
		return;
	}
#pragma message "Check if busy"
	QDialog::accept();
}

QString ChangeLoginDialog::getNewLogin()
{
	return new_login;
}

ChangeLoginDialog::~ChangeLoginDialog()
{
	delete ui;
}
