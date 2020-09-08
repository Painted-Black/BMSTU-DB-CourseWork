#pragma once

#include <QWidget>
#include <QDialog>
#include "contacts.h"
#include "types/animal_medical_record.h"

namespace Ui
{
	class animal_widget;
	class chip_widget;
	class add_constract_widget;
	class address_widget;
	class PassportWidget;
	class contacts_widget;
	class TextEditor;
	class client;
}

class AnimalEditWidget : public QWidget
{
	Q_OBJECT
public:
	explicit AnimalEditWidget(QWidget *parent = nullptr);
	void update();
	void show(const QUrl &, std::chrono::milliseconds, const QByteArray&);
	bool isFills() const;
	bool isEdit() const;
	AnimalMedicalRecord getEditedAnimalMedicalRecord();
	const AnimalMedicalRecord& getAnimalMedicalRecord() const;
	void updateClientData();
	void setClientData(const Client &);
private:
	void activeInfoDialog();
	void activeSignDialog();
	void activeClientDialog();
	QString showInfoDialog(const QString&);
	void showContract();

private:
	Ui::animal_widget* ui;
	Ui::chip_widget* chip_ui;
	Ui::add_constract_widget* contract_ui;
	Ui::TextEditor *info_dlg_ui;
	Ui::client* client_dlg_ui;
	Ui::address_widget* address_dlg_ui;
	Ui::PassportWidget* passport_dlg_ui;
	QDialog* info_dlg;
	QDialog* client_dlg;
	QWidget* contract;
	QWidget* chip;
	Contacts* contact;
	AnimalMedicalRecord animal_record;
};

