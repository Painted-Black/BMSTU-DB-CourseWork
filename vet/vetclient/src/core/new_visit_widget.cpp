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
#include "chose_animal_dialog.h"
#include "core/network/network_fetcher.h"
#include "utils/singlenton.h"
#include "core/popup.h"
#include "config/config.h"
#include "utils/utils.h"

NewVisitWidget::NewVisitWidget(QWidget *parent)
	: QWidget(parent), ui(new Ui::visit_widget()), model(new PrescribingsTableModel())
{
	ui->setupUi(this);

	QDate current_date = QDate::currentDate();
	ui->visit_date_dateEdit->setDate(current_date);
	ui->visit_date_dateEdit->setEnabled(false);
	ui->next_visit_dateEdit->setDate(current_date);
	ui->next_visit_dateEdit->setMinimumDate(current_date);

	connect(ui->save_pushButton, &QPushButton::released, this, &NewVisitWidget::handle_save_button);
	connect(ui->chose_animal_pushButton, &QPushButton::released, this, &NewVisitWidget::choseAnimal);
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

	bool is_ok = false;
	Visit vis = getVisit(&is_ok);

	if (is_ok == false)
	{
		auto& popup = Singlenton<PopUp>::getInstance();
		popup.setPopupText("Не все поля заполненны корректно.");
		popup.show();
		return;
	}

	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest request(cfg.getUrlNewVisit());
    request.setRawHeader("Authorization", QByteArray("Explicit: ").append(access_data.getPassword()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    NetworkFetcher fetcher;
	QByteArray raw_data = visitSerialize(vis, animal_id);
	auto reply = fetcher.httpPost(request, raw_data, cfg.getTimeout());
    int32_t code = std::get<0>(reply);
	auto& popup = Singlenton<PopUp>::getInstance();
    if (code == -1)
    {
		popup.setPopupText("Нет соединения с интернетом или доступа к серверу.");
		popup.show();
		return;
    }
    if (code != 201)
    {
		popup.setPopupText("Возникла ошибка.");
		popup.show();
		return;
    }
	// ok
	qDebug() << Q_FUNC_INFO << "Saved";
	popup.setPopupText("Данные осмотра успешно сохранены.");
	popup.show();
	readOnly();
}

Visit NewVisitWidget::getVisit(bool *is_ok)
{
	Visit vis;
	AnimalState state;
	*is_ok = false;

	QString gen_state_str = ui->general_state_comboBox->currentText();
	GeneralState gen_state;
	if (gen_state.fromString(gen_state_str) == false)
	{
		qDebug() << Q_FUNC_INFO << "Unable to read general state type";
		return vis;
	}
	int32_t pulse = ui->pulse_spinBox->value();
	if (pulse <= 0)
	{
		qDebug() << Q_FUNC_INFO << "Unable to read pulse";
		return vis;
	}

	float weight = ui->weight_doubleSpinBox->value();
	if (weight <= 0)
	{
		qDebug() << Q_FUNC_INFO << "Unable to read weight";
		return vis;
	}

	int32_t AP_1 = ui->ap_1_spinBox->value();
	int32_t AP_2 = ui->ap_2_spinBox->value();
	if (AP_1 <= 0 || AP_2 <= 0)
	{
		qDebug() << Q_FUNC_INFO << "Unable to read ap";
		return vis;
	}
	QString AP = QVariant(AP_1).toString() + "/" + QVariant(AP_2).toString();

	float temperature = ui->temperature_doubleSpinBox->value();
	if (temperature <= 0)
	{
		qDebug() << Q_FUNC_INFO << "Unable to read temperature";
		return vis;
	}

	int32_t cfr = ui->cfr_spinBox->value();
	if (cfr <= 0)
	{
		qDebug() << Q_FUNC_INFO << "Unable to read cfr";
		return vis;
	}

	int32_t resp_rate = ui->resp_rate_spinBox->value();
	if (resp_rate <= 0)
	{
		qDebug() << Q_FUNC_INFO << "Unable to read resp rate";
		return vis;
	}

	state.setGeneral(gen_state);
	state.setPulse(pulse);
	state.setWeight(weight);
	state.setAP(AP);
	state.setTemperature(temperature);
	state.setResp_rate(resp_rate);

	Staff doctor = access_data.getOwner();
//	bool is_ambulatoty = ui->ambularory_checkBox->isChecked();
	QDate visit_date = QDate::fromString(ui->visit_date_dateEdit->text(), "dd.MM.yyyy");

	QString owner_dynamics = ui->owner_dynamics_comboBox->currentText();
	OwnerDynamic dynamics;
	if (dynamics.fromString(owner_dynamics) == false)
	{
		qDebug() << Q_FUNC_INFO << "Unable to read owner dynamics type";
		return vis;
	}
	QString histoty_disease = ui->anamnesis_lineEdit->text();
	if (histoty_disease.isEmpty())
	{
		qDebug() << Q_FUNC_INFO << "Unable to read anamnesis";
		return vis;
	}
	QString diagnosis = ui->diagnosis_lineEdit->text();
	if (diagnosis.isEmpty())
	{
		qDebug() << Q_FUNC_INFO << "Unable to read diagnosis";
		return vis;
	}

	QString rec = ui->recommendations_lineEdit->text();
	if (rec.isEmpty())
	{
		qDebug() << Q_FUNC_INFO << "Unable to read recommendations";
		return vis;
	}

	bool next_visit = ui->next_visit_checkBox->isChecked();
	if (next_visit == true)
	{
		QDate next_visit_date = QDate::fromString(ui->next_visit_dateEdit->text(), "dd.MM.yyyy");
		vis.setNext_visit(next_visit_date);
	}

	QString notes = ui->note_lineEdit->text();

	if (animal_id == -1)
	{
		qDebug() << Q_FUNC_INFO << "Animal id is empty!";
		return vis;
	}
	Prescribings pr = model->getPresctibings();

	vis.setDoctor(doctor);
//	vis.setAmbulatury(is_ambulatoty);
	vis.setVisit_date(visit_date);
	vis.setOwner_dynamics(dynamics);
	vis.setHistory_disease(histoty_disease);
	vis.setCur_state(state);
	vis.setDiagnosis(diagnosis);
	vis.setRecommendations(rec);
	vis.setNote(notes);
	vis.setPrescribings(pr);
	*is_ok = true;
	return vis;
}

void NewVisitWidget::setAccessData(const AccessData &value)
{
	access_data = value;
}

void NewVisitWidget::readOnly()
{
//	ui->chose_animal_pushButton->setEnabled(false);
	ui->chose_animal_pushButton->hide();
	ui->visit_date_dateEdit->setEnabled(false);
	ui->anamnesis_lineEdit->setEnabled(false);
	ui->owner_dynamics_comboBox->setEnabled(false);
	ui->general_state_groupBox->setEnabled(false);
	ui->pulse_spinBox->setEnabled(false);
	ui->weight_doubleSpinBox->setEnabled(false);
	ui->ap_1_spinBox->setEnabled(false);
	ui->ap_2_spinBox->setEnabled(false);
	ui->temperature_doubleSpinBox->setEnabled(false);
	ui->cfr_spinBox->setEnabled(false);
	ui->resp_rate_spinBox->setEnabled(false);
	ui->diagnosis_lineEdit->setEnabled(false);
//	ui->add_prescr_toolButton->setEnabled(false);
//	ui->delete_prescr_toolButton->setEnabled(false);
	ui->add_prescr_toolButton->hide();
	ui->delete_prescr_toolButton->hide();
	ui->recommendations_lineEdit->setEnabled(false);
	ui->next_visit_checkBox->setEnabled(false);
	ui->next_visit_dateEdit->setEnabled(false);
	ui->note_lineEdit->setEnabled(false);
	ui->save_pushButton->hide();
}

void NewVisitWidget::choseAnimal()
{
    qDebug() << Q_FUNC_INFO << "Chose animal...";
    ChoseAnimalDialog chose_dialog(this);
    chose_dialog.setAccessData(access_data);
    chose_dialog.show();
    if (chose_dialog.exec() == QDialog::Rejected)
    {
        return;
    }

    animal_id = chose_dialog.property("animal_id").value<uint64_t>();
    QString animal_name = chose_dialog.property("animal_name").toString();
    QString animal_species = chose_dialog.property("animal_species").toString();

    ui->name_lineEdit->setText(animal_name);
	ui->species_lineEdit->setText(animal_species);
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
	if (selected_rows.size() != 0)
	{
		int i = selected_rows.begin()->row();
		model->removeMed(selected_rows.at(0).data().toString(), i);
	}
//	for (int i = 0; i < rows_selected; ++i)
//	{
//		model->removeMed(selected_rows.at(i).data().toString(), i);
//	}
	//	Prescribings pr = model->getPresctibings();
}
