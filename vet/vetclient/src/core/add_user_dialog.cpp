#include "add_user_dialog.h"
#include "ui_add_user_dialog.h"
#include "types/json_fields.h"
#include "types/user_data.h"
#include "chose_staff_dialog.h"

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
	AccessLevel level;
	level.fromString(acc_lvl);
	data.setLevel(level);
	Staff s;
	s.setId(staff_id);
	data.setOwner(s);
	password = QVariant(pass1).toByteArray();
	data.setPassword(password);
	QDialog::accept();
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
	qDebug() << "Id: " << staff_id;
}

void AddUserDialog::setAccessData(const QByteArray &value)
{
	access_data = value;
}


