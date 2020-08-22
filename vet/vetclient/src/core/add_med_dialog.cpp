#include "add_med_dialog.h"
#include "ui_add_med_dialog.h"

AddMedDialog::AddMedDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMedDialog)
{
    ui->setupUi(this);
    qRegisterMetaType<Medicine>("Medicine");

    ui->type_comboBox->addItem(RusInjectionTypes::rus_injection_ingest);
    ui->type_comboBox->addItem(RusInjectionTypes::rus_injection_intravenous);
    ui->type_comboBox->addItem(RusInjectionTypes::rus_injection_subcutaneous);
    ui->type_comboBox->addItem(RusInjectionTypes::rus_injection_intramuscular);
}

void AddMedDialog::accept()
{
    QString name = ui->name_lineEdit->text();
    QString dose = ui->dose_lineEdit->text();
    QString type = ui->type_comboBox->currentText();
    QString term = ui->term_lineEdit->text();
    QString freq = ui->freq_lineEdit->text();
    med.setName(name);
    med.setDosage(dose);
    InjectionType _type;
    _type.fromString(type);
    med.setType(_type);
    med.setTerm_of_taking(term);
    med.setFrequency_of_medication(freq);
    QDialog::accept();
}

AddMedDialog::~AddMedDialog()
{
    delete ui;
}

Medicine AddMedDialog::getMed()
{
    return med;
}
