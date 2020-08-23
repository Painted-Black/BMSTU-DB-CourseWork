#pragma once

#include <QWidget>
#include <QDialog>
#include "types/animal_medical_record.h"

namespace Ui
{
	class animal_widget;
	class chip_widget;
	class add_constract_widget;
	class TextEditor;
}

class AnimalEditWidget : public QWidget
{
	Q_OBJECT
public:
	explicit AnimalEditWidget(QWidget *parent = nullptr);
	void show(const QUrl &, const QByteArray&);

private:
	void activeInfoDialog();
	void activeSignDialog();
	QString showInfoDialog(const QString&);
	void showContract();

private:
	Ui::animal_widget* ui;
	Ui::chip_widget* chip_ui;
	Ui::add_constract_widget* contract_ui;
	Ui::TextEditor *info_dlg_ui;
	QDialog* info_dlg;
	QWidget* contract;
	QWidget* chip;
	AnimalMedicalRecord animal_record;
};

