#pragma once

#include <QWidget>

namespace Ui
{
	class add_constract_widget;
}

class AddContractWidget : public QWidget
{
public:
	AddContractWidget(QWidget* = nullptr);

private:
	Ui::add_constract_widget* ui;
};

