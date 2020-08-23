#pragma once

#include <QWidget>
#include <QDialog>
#include "types/animal_medical_record.h"

namespace Ui
{
	class animal_widget;
	class chip_widget;
	class add_constract_widget;
	class address_widget;
	class passport_widget;
	class contacts_widget;
	class TextEditor;
	class client;
}

class AnimalEditWidget : public QWidget
{
	Q_OBJECT
public:
	explicit AnimalEditWidget(QWidget *parent = nullptr);
	void show(const QUrl &, const QByteArray&);
	bool isFills() const;
	bool isEdit() const;
	AnimalMedicalRecord getAnimalMedicalRecort();
private:
	void activeInfoDialog();
	void activeSignDialog();
	void active();
	QString showInfoDialog(const QString&);
	void showContract();

private:
	Ui::animal_widget* ui;
	Ui::chip_widget* chip_ui;
	Ui::add_constract_widget* contract_ui;
	Ui::TextEditor *info_dlg_ui;
	Ui::client* client_dlg_ui;
	Ui::address_widget* address_dlg_ui;
	Ui::passport_widget* passport_dlg_ui;
	Ui::contacts_widget* contact_dlg_ui;
	QDialog* info_dlg;
	QDialog* client_dlg;
	QWidget* contract;
	QWidget* chip;
	AnimalMedicalRecord animal_record;
};

