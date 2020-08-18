#pragma once

#include <QWidget>
#include <QListView>
#include <QNetworkAccessManager>

#include "core/model/animallistmodel.h"
#include "types/animal_medical_record.h"
#include "delegate/animallistdelegate.h"

namespace Ui
{
	class Form;
}

class AnimalListWidget : public QWidget
{
	Q_OBJECT
public:
	AnimalListWidget(QWidget* = nullptr);
	void show(const QUrl&, const QByteArray&);

Q_SIGNALS:
	void interruptRequestData();

private:
	void response(QNetworkReply*);

private:
	AnimalListModel* model;
	AnimalListDelegate* delegate;
	QListView* view;
	QNetworkAccessManager* manager;
};
