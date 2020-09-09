#pragma once

#include <QWidget>
#include <QListWidget>
#include "types/short_animal_info.h"

namespace Ui
{
	class Form;
}

class AnimalListWidget : public QWidget
{
	Q_OBJECT
public:
	AnimalListWidget(QWidget* = nullptr);
	bool show(const QUrl&, std::chrono::milliseconds tout, const QByteArray&);
	void addAnimal(const ShortAnimalInfo&, const QByteArray &);
private:
	void addWidget(const ShortAnimalInfo&, const QByteArray &);
	void selectItemWidget(QListWidgetItem*);

Q_SIGNALS:
	void selectItem(uint64_t);

private:
	QListWidget* view;
};
