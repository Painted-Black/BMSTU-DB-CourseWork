#pragma once

#include <QWidget>
#include <QNetworkAccessManager>
#include "types/user_data.h"
#include "types/animal_medical_record.h"
#include "types/client.h"
#include "types/contract.h"

namespace Ui
{
    class visit_widget;
}

class NewVisitWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NewVisitWidget(QWidget *parent = nullptr);
    void update();
    void setAccessData(const AccessData &value);
private:
    void choseAnimal();
private slots:
    void handle_save_button();
    void handle_chose_animal_btn();
private:
    Ui::visit_widget* ui;
    AccessData access_data;
    AnimalMedicalRecord chosed_animal;
};

