#pragma once

#include <QWidget>

namespace Ui
{
	class animal_widget;
}

class AnimalEditWidget : public QWidget
{
	Q_OBJECT
public:
	explicit AnimalEditWidget(QWidget *parent = nullptr);
	void update();

private:
	Ui::animal_widget* ui;
};

