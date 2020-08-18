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

NewVisitWidget::NewVisitWidget(QWidget *parent) : QWidget(parent), ui(new Ui::visit_widget())
{
    ui->setupUi(this);
    connect(ui->save_pushButton, SIGNAL(released()), this, SLOT(handle_save_button()));
    connect(ui->chose_animal_pushButton, SIGNAL(released()), this, SLOT(choseAnimal()));
    connect(ui->save_pushButton, SIGNAL(released()), this, SLOT(handle_save_button()));

    ui->owner_dynamics_comboBox->addItem(RusOwnerDynamicsType::rus_owner_dynamics_stably);
    ui->owner_dynamics_comboBox->addItem(RusOwnerDynamicsType::rus_owner_dynamics_better);
    ui->owner_dynamics_comboBox->addItem(RusOwnerDynamicsType::rus_owner_dynamics_worse);

    ui->general_state_comboBox->addItem(RusGeneralStateType::rus_general_state_good);
    ui->general_state_comboBox->addItem(RusGeneralStateType::rus_general_state_middle);
    ui->general_state_comboBox->addItem(RusGeneralStateType::rus_general_state_bad);

    ui->tableWidget->setColumnCount(7);
    QTableWidgetItem* num_header = new QTableWidgetItem("№");
    QTableWidgetItem* name_header = new QTableWidgetItem("Название");
    QTableWidgetItem* dosage_header = new QTableWidgetItem("Дозировка");
    QTableWidgetItem* type_header = new QTableWidgetItem("Вид приема");
    QTableWidgetItem* freq_header = new QTableWidgetItem("Частота приема");
    QTableWidgetItem* terms_header = new QTableWidgetItem("Длительность приема");
    QTableWidgetItem* notes_header = new QTableWidgetItem("Примечание");

    ui->tableWidget->setHorizontalHeaderItem(0, num_header);
    ui->tableWidget->setHorizontalHeaderItem(1, name_header);
    ui->tableWidget->setHorizontalHeaderItem(2, dosage_header);
    ui->tableWidget->setHorizontalHeaderItem(3, type_header);
    ui->tableWidget->setHorizontalHeaderItem(4, freq_header);
    ui->tableWidget->setHorizontalHeaderItem(5, terms_header);
    ui->tableWidget->setHorizontalHeaderItem(6, notes_header);

    ui->tableWidget->adjustSize();

//    ui->prescribings_tableView.
}

void NewVisitWidget::update()
{
    const Staff& staff = access_data.getOwner();
    const Passport& pass = staff.getPassport();
    const Position& staff_pos = staff.getPosition();
    QString staff_snp = pass.getSurname() + " " + pass.getName() + " " + pass.getPatronymic();

    ui->input_specialist_label->setText(staff_pos.getTitle());
    ui->input_visit_by_label->setText(staff_snp);
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

void NewVisitWidget::handle_chose_animal_btn()
{
    qDebug() << Q_FUNC_INFO << "Chose animal...";
#pragma message "TODO"
}

void NewVisitWidget::setAccessData(const AccessData &value)
{
    access_data = value;
}

void NewVisitWidget::choseAnimal()
{
#pragma message "TODO"
}
