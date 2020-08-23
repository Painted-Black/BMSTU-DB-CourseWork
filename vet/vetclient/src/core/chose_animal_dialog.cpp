#include "chose_animal_dialog.h"
#include "ui_chose_animal_dialog.h"
#include "animal_list_item_widget.h"
#include "animal_edit_widget.h"
#include "mainwindow.h"
#include "chose_animal_full_dialog.h"
#include <QBoxLayout>
#include <QPushButton>

ChoseAnimalDialog::ChoseAnimalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoseAnimalDialog)
{
    ui->setupUi(this);
}

ChoseAnimalDialog::~ChoseAnimalDialog()
{
    delete ui;
}

void ChoseAnimalDialog::animalInfoWidget(uint64_t id)
{
    ChoseAnimalFullDialog full_dial(this);
    full_dial.setAccess_data(access_data);
    full_dial.show(id);
    if (full_dial.exec() == QDialog::Rejected)
    {
        return;
    }
    animal_id = id;
    accept();
}

void ChoseAnimalDialog::setAccess_data(const AccessData &value)
{
    access_data = value;
}

void ChoseAnimalDialog::show()
{
    QBoxLayout* layout = new QVBoxLayout();
    AnimalListWidget* aiw = new AnimalListWidget(ui->main_widget);

    connect(aiw, &AnimalListWidget::selectItem, this, &ChoseAnimalDialog::animalInfoWidget);

    aiw->show(QUrl("http://127.0.0.1:4446/animals/all/short"), access_data.getPassword());
    layout->addWidget(aiw);
    ui->main_widget->setLayout(layout);
}

uint64_t ChoseAnimalDialog::getAnimal_id() const
{
    return animal_id;
}
