#pragma once

#include <QDialog>
#include "types/animal_medical_record.h"
#include "types/user_data.h"

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
    void setAccess_data(const AccessData &value);
    void show();
    uint64_t getAnimal_id() const;

private:
    Ui::ChoseAnimalDialog *ui;
    uint64_t animal_id;
    QString animal_name;
    QString animal_species;
    AccessData access_data;
};

