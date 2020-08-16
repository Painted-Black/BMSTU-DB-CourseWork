#pragma once

#include <QWidget>
#include <QListWidget>

#include "types/animal_medical_record.h"

namespace Ui
{
	class Form;
}

class AnimalListItemWidget : public QWidget
{
	Q_OBJECT
public:
	struct AnimalData final
	{
		uint64_t uid;
		QString name;
		QString spec;
		QDate birth;
	};
public:
	explicit AnimalListItemWidget(QWidget *parent = nullptr);
	void view(const AnimalMedicalRecord& rec);

private:
	Ui::Form* ui;
};

class AnimalListWidget : public QWidget
{
	Q_OBJECT
public:
	AnimalListWidget();
	bool loadFromJson(const QByteArray&);

	void view();
private:
	QList<AnimalListItemWidget::AnimalData> widgets;
	QListWidget widget;
};
