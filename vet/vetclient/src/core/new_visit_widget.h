#pragma once

#include <QWidget>
#include "types/user_data.h"
#include "types/animal_medical_record.h"
#include "types/client.h"
#include "types/contract.h"
#include "model/prescribings_table_model.h"
#include "types/visit.h"

namespace Ui
{
	class visit_widget;
}

class NewVisitWidget : public QWidget
{
	Q_OBJECT
public:
	enum Mode
	{
		SHOW,
		ADD,
		EDIT
	};
	explicit NewVisitWidget(Mode mode = ADD, QWidget *parent = nullptr);
	void update();
	void setAccessData(const AccessData &value);
	void readOnly();
	void setVisitShow(const Visit &visitShow);

	void setPassword(const QByteArray &password);

private:
	void handle_save_button();
	void choseAnimal();
	void add_prescr_btn();
	void delete_prescr_btn();
	Visit getVisit(bool *is_ok);
private:
	Ui::visit_widget* ui;
	AccessData access_data;
	PrescribingsTableModel* model;
	int64_t animal_id = -1;
	Visit mVisitShow;
	QByteArray mPassword;
};

