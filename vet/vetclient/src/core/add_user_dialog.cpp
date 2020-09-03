#include "add_user_dialog.h"
#include "ui_add_user_dialog.h"

AddUserDialog::AddUserDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddUserDialog)
{
	ui->setupUi(this);
}

AddUserDialog::~AddUserDialog()
{
	delete ui;
}
