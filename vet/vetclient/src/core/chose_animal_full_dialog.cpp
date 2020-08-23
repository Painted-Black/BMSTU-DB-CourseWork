#include "chose_animal_full_dialog.h"
#include "ui_chose_animal_full_dialog.h"
#include "animal_edit_widget.h"

ChoseAnimalFullDialog::ChoseAnimalFullDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoseAnimalFullDialog)
{
    ui->setupUi(this);
}

ChoseAnimalFullDialog::~ChoseAnimalFullDialog()
{
    delete ui;
}

void ChoseAnimalFullDialog::show(uint64_t id)
{
    QVBoxLayout* layout = new QVBoxLayout();
    AnimalEditWidget* aiw = new AnimalEditWidget(ui->main_widget);
    QUrl url(QString("http://127.0.0.1:4446/animals?id=%1").arg(static_cast<qulonglong>(id)));

    aiw->show(url, access_data.getPassword());
    layout->addWidget(aiw);
    ui->main_widget->setLayout(layout);
    ui->main_widget->show();
}

void ChoseAnimalFullDialog::setAccess_data(const AccessData &value)
{
    access_data = value;
}
