#include "chose_animal_full_dialog.h"
#include "ui_chose_animal_full_dialog.h"
#include "animal_edit_widget.h"

ChoseAnimalFullDialog::ChoseAnimalFullDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoseAnimalFullDialog),
    aiw(new AnimalEditWidget(this))
{
    ui->setupUi(this);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(aiw);
    ui->main_widget->setLayout(layout);
}

ChoseAnimalFullDialog::~ChoseAnimalFullDialog()
{
    delete ui;
}

void ChoseAnimalFullDialog::show(uint64_t id)
{
    QUrl url(QString("http://127.0.0.1:4446/animals?id=%1").arg(static_cast<qulonglong>(id)));
    aiw->show(url, access_data.getPassword());
    ui->main_widget->show();
}

void ChoseAnimalFullDialog::setAccess_data(const AccessData &value)
{
    access_data = value;
}

const AnimalMedicalRecord &ChoseAnimalFullDialog::getAnimalRecord() const
{
    return aiw->getAnimalRecord();
}
