#include "chose_access_leveldialog.h"
#include "ui_chose_access_leveldialog.h"

#include "types/json_fields.h"

ChoseAccessLevelDialog::ChoseAccessLevelDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ChoseAccessLevelDialog)
{
	ui->setupUi(this);
	ui->access_comboBox->addItem(AccessLevelType::access_vet);
	ui->access_comboBox->addItem(AccessLevelType::access_main);
	ui->access_comboBox->addItem(AccessLevelType::access_registry);
	ui->access_comboBox->addItem(AccessLevelType::access_admin);
}

ChoseAccessLevelDialog::~ChoseAccessLevelDialog()
{
	delete ui;
}

void ChoseAccessLevelDialog::setOldAccesslevel(const QString &level)
{
	if (level == AccessLevelType::access_vet)
	{
		ui->access_comboBox->setCurrentIndex(0);
	}
	else if (level == AccessLevelType::access_main)
	{
		ui->access_comboBox->setCurrentIndex(1);
	}
	else if (level == AccessLevelType::access_admin)
	{
		ui->access_comboBox->setCurrentIndex(3);
	}
	else if (level == AccessLevelType::access_registry)
	{
		ui->access_comboBox->setCurrentIndex(2);
	}
}

QString ChoseAccessLevelDialog::getAccessLevel() const
{
	return access_level;
}

void ChoseAccessLevelDialog::accept()
{
	access_level = ui->access_comboBox->currentText();
	QDialog::accept();
}
