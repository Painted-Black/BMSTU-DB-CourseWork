#pragma once

#include <QDialog>
#include "types/user_data.h"
#include "types/animal_medical_record.h"
#include "animal_edit_widget.h"

namespace Ui {
class ChoseAnimalFullDialog;
}

class ChoseAnimalFullDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChoseAnimalFullDialog(QWidget *parent = nullptr);
    ~ChoseAnimalFullDialog();
    void show(uint64_t id);
    void setAccess_data(const AccessData &value);
    const AnimalMedicalRecord& getAnimalRecord() const;

private:
    Ui::ChoseAnimalFullDialog *ui;
    AccessData access_data;
    AnimalEditWidget* aiw;
};

