#include "fire_dialog.h"
#include "ui_fire_dialog.h"

FireDialog::FireDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::FireDialog)
{
	ui->setupUi(this);
	QDate current_date = QDate::currentDate();
	ui->dateEdit->setDate(current_date);
	ui->dateEdit->setMinimumDate(current_date);
}

FireDialog::~FireDialog()
{
	delete ui;
}

void FireDialog::accept()
{
	mFireDate = ui->dateEdit->date();
	QDialog::accept();
}

QDate FireDialog::getFireDate() const
{
	return mFireDate;
}
