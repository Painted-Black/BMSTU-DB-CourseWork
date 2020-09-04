#include "chose_staff_full_dialog.h"
#include "ui_chose_staff_full_dialog.h"

ChoseStaffFullDialog::ChoseStaffFullDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ChoseStaffFullDialog)
{
	ui->setupUi(this);
}

ChoseStaffFullDialog::~ChoseStaffFullDialog()
{
	delete ui;
}

void ChoseStaffFullDialog::setPassword(const QByteArray &pass)
{
	password = pass;
}

void ChoseStaffFullDialog::show(const ShortStaffInfo& user_info)
{
	ui->name_lineEdit->setText(user_info.getName());
	ui->surname_lineEdit->setText(user_info.getSurname());
	ui->patr_lineEdit->setText(user_info.getPatr());
	ui->pos_titile_lineEdit->setText(user_info.getPosition());
	ui->empl_dateEdit->setDate(user_info.getEmpl());
	QDate fire_date = user_info.getFire();
	if (fire_date.isValid())
	{
		ui->fire_dateEdit->setDate(fire_date);
	}
	else
	{
		ui->fire_label->hide();
		ui->fire_dateEdit->hide();
	}
}
