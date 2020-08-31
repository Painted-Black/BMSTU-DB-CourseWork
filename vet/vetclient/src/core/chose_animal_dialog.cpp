#include "chose_animal_dialog.h"
#include "ui_chose_animal_dialog.h"
#include "animal_list_item_widget.h"
#include "animal_edit_widget.h"
#include "mainwindow.h"
#include "chose_animal_full_dialog.h"
#include "utils/singlenton.h"
#include "config/config.h"
#include <QBoxLayout>
#include <QPushButton>

ChoseAnimalDialog::ChoseAnimalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoseAnimalDialog),
    aiw(new AnimalListWidget(this))
{
    ui->setupUi(this);    
    connect(aiw, &AnimalListWidget::selectItem, this, &ChoseAnimalDialog::animalInfoWidget);
    QBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(aiw);
    ui->main_widget->setLayout(layout);
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
    const auto& anim_rec = full_dial.getAnimalRecord();
    setProperty("animal_id", QVariant::fromValue(id));
    setProperty("animal_name", anim_rec.getName());
    setProperty("animal_species", anim_rec.getSpecies());
    accept();
}

void ChoseAnimalDialog::setAccessData(const AccessData &value)
{
    access_data = value;
}

void ChoseAnimalDialog::show()
{
	auto& cfg = Singlenton<Config>::getInstance();
	aiw->show(QUrl("http://127.0.0.1:4446/animals/all/short"), cfg.getTimeout(), access_data.getPassword());
}
