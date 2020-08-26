#pragma once

#include <QWidget>
#include "types/user_data.h"
#include "types/animal_medical_record.h"
#include "types/client.h"
#include "types/contract.h"
#include "model/prescribings_table_model.h"

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
	void handle_save_button();
	void choseAnimal();
	void add_prescr_btn();
	void delete_prescr_btn();
private:
	Ui::visit_widget* ui;
	AccessData access_data;
//	Prescribings pres;
	AnimalMedicalRecord chosed_animal;
	PrescribingsTableModel* model;
};

