#include <QPushButton>
#include <QDebug>
#include <QDate>
#include "new_visit_widget.h"
#include "ui_visit.h"
#include "types/staff.h"
#include "types/position.h"
#include "types/passport.h"
#include "types/json_fields.h"
#include "types/visit.h"
#include "types/prescribings.h"
#include "add_med_dialog.h"

NewVisitWidget::NewVisitWidget(QWidget *parent)
	: QWidget(parent), ui(new Ui::visit_widget()), model(new PrescribingsTableModel())
{
	ui->setupUi(this);
	connect(ui->save_pushButton, &QPushButton::released, this, &NewVisitWidget::handle_save_button);
	connect(ui->chose_animal_pushButton, &QPushButton::released, this, &NewVisitWidget::choseAnimal);
	connect(ui->save_pushButton, &QPushButton::released, this, &NewVisitWidget::handle_save_button);
	connect(ui->add_prescr_toolButton, &QPushButton::released, this, &NewVisitWidget::add_prescr_btn);
	connect(ui->delete_prescr_toolButton, &QPushButton::released, this, &NewVisitWidget::delete_prescr_btn);

	ui->owner_dynamics_comboBox->addItem(RusOwnerDynamicsType::rus_owner_dynamics_stably);
	ui->owner_dynamics_comboBox->addItem(RusOwnerDynamicsType::rus_owner_dynamics_better);
	ui->owner_dynamics_comboBox->addItem(RusOwnerDynamicsType::rus_owner_dynamics_worse);

	ui->general_state_comboBox->addItem(RusGeneralStateType::rus_general_state_good);
	ui->general_state_comboBox->addItem(RusGeneralStateType::rus_general_state_middle);
	ui->general_state_comboBox->addItem(RusGeneralStateType::rus_general_state_bad);
}

void NewVisitWidget::update()
{
	const Staff& staff = access_data.getOwner();
	const Passport& pass = staff.getPassport();
	const Position& staff_pos = staff.getPosition();
	QString staff_snp = pass.getSurname() + " " + pass.getName() + " " + pass.getPatronymic();
	ui->input_specialist_label->setText(staff_pos.getTitle());
	ui->input_visit_by_label->setText(staff_snp);
	ui->prescr_tableView->setModel(model);

	int model_col_count = model->columnCount();
	for (int i = 0; i < model_col_count; ++i)
	{
		ui->prescr_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
	}
}

void NewVisitWidget::handle_save_button()
{
	qDebug() << Q_FUNC_INFO << "Saving...";

	bool is_ambulatoty = ui->ambularory_checkBox->isChecked();
	QDate visit_date = QDate::fromString(ui->visit_date_dateEdit->text());
	QString histoty_disease = ui->anamnesis_lineEdit->text();
	QString owner_dynamics = ui->owner_dynamics_comboBox->currentText();
	OwnerDynamic dynamics;
	if (dynamics.fromString(owner_dynamics) == false)
	{
		qDebug() << Q_FUNC_INFO << "Unable to read owner dynamics type";
	}

	QString gen_state_str = ui->general_state_comboBox->currentText();
	GeneralState gen_state;
	if (gen_state.fromString(gen_state_str) == false)
	{
		qDebug() << Q_FUNC_INFO << "Unable to read general state type";
	}

	uint32_t pulse = ui->pulse_spinBox->value();
	float weight = ui->weight_doubleSpinBox->value();
	uint32_t AP_1 = ui->ap_1_spinBox->value();
	uint32_t AP_2 = ui->ap_2_spinBox->value();
	QString AP = QVariant(AP_1).toString() + " / " + QVariant(AP_2).toString();
	float temperature = ui->temperature_doubleSpinBox->value();
	uint32_t cfr = ui->cfr_spinBox->value();
	uint32_t resp_rate = ui->resp_rate_spinBox->value();
	QString diagnosis = ui->diagnosis_lineEdit->text();
	bool next_visit = ui->next_visit_checkBox->isChecked();
	QDate next_visit_date = QDate::fromString(ui->next_visit_dateEdit->text());
	QString notes = ui->note_lineEdit->text();
	QString rec = ui->recommendations_lineEdit->text();

	Prescribings pr;

	if (histoty_disease.isEmpty())
	{
		qDebug() << "Disease history is empty!";
	}
	if (diagnosis.isEmpty())
	{
		qDebug() << "Diagnosis is empty!";
	}
	if (rec.isEmpty())
	{
		qDebug() << "Recommendations is empty!";
	}


	qDebug() << Q_FUNC_INFO << "Saved";
}

void NewVisitWidget::setAccessData(const AccessData &value)
{
	access_data = value;
}

void NewVisitWidget::choseAnimal()
{
	qDebug() << Q_FUNC_INFO << "Chose animal...";
#pragma message "TODO"
}

void NewVisitWidget::add_prescr_btn()
{
	qDebug() << Q_FUNC_INFO << "Add prescr...";
	AddMedDialog add_med_dialog;
	if (add_med_dialog.exec() == QDialog::Accepted)
	{
		Medicine med = add_med_dialog.getMed();
		model->addMed(med);
//		pres.append(med);
	}
}

void NewVisitWidget::delete_prescr_btn()
{
	qDebug() << Q_FUNC_INFO << "Delete prescr...";
	QItemSelectionModel *select = ui->prescr_tableView->selectionModel();
	QModelIndexList selected_rows = select->selectedRows();
	int rows_selected = selected_rows.size();
	for (int i = 0; i < rows_selected; ++i)
	{
		model->removeMed(selected_rows.at(i).data().toString(), i);
	}
//	Prescribings pr = model->getPresctibings();
}
