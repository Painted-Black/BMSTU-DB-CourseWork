#include "add_shedule_item_dialog.h"
#include "ui_add_shedule_item_dialog.h"
#include "types/json_fields.h"
#include "utils/singlenton.h"
#include "core/popup.h"

AddSheduleItemDialog::AddSheduleItemDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddSheduleItemDialog)
{
	ui->setupUi(this);
	ui->day_comboBox->addItem(RussianDayOfWeekType::rus_day_of_week_sun);
	ui->day_comboBox->addItem(RussianDayOfWeekType::rus_day_of_week_mon);
	ui->day_comboBox->addItem(RussianDayOfWeekType::rus_day_of_week_tue);
	ui->day_comboBox->addItem(RussianDayOfWeekType::rus_day_of_week_wed);
	ui->day_comboBox->addItem(RussianDayOfWeekType::rus_day_of_week_thu);
	ui->day_comboBox->addItem(RussianDayOfWeekType::rus_day_of_week_fri);
	ui->day_comboBox->addItem(RussianDayOfWeekType::rus_day_of_week_sat);

	hideErrorLabels();
}

AddSheduleItemDialog::~AddSheduleItemDialog()
{
	delete ui;
}

void AddSheduleItemDialog::accept()
{
	hideErrorLabels();
	QString cab = ui->cab_lineEdit->text();
	if (cab.isEmpty() == true)
	{
		ui->cab_error_label->show();
		return;
	}
	QString day = ui->day_comboBox->currentText();
	DayOfWeek day_t;
	day_t.fromString(day);

	QTime start = ui->start_timeEdit->time();
	QTime end = ui->emd_timeEdit->time();

	mNewShedule.setDay_of_week(day_t);
	mNewShedule.setCabinet(cab);
	mNewShedule.setStart(start);
	mNewShedule.setEnd(end);

	QDialog::accept();
}

void AddSheduleItemDialog::hideErrorLabels()
{
	ui->cab_error_label->hide();
}

Schedule AddSheduleItemDialog::newShedule() const
{
	return mNewShedule;
}
