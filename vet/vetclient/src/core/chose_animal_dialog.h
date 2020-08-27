#pragma once

#include <QDialog>
#include "types/animal_medical_record.h"
#include "types/user_data.h"
#include "animal_list_item_widget.h"

namespace Ui {
class ChoseAnimalDialog;
}

class ChoseAnimalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChoseAnimalDialog(QWidget *parent = nullptr);
    ~ChoseAnimalDialog();
    void animalInfoWidget(uint64_t id);
    void setAccessData(const AccessData &value);
    void show();

private:
    Ui::ChoseAnimalDialog *ui;
    uint64_t animal_id;
    QString animal_name;
    QString animal_species;
    AccessData access_data;
    AnimalListWidget* aiw;
};

