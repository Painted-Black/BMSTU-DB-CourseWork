#pragma once

#include <QWidget>

namespace Ui
{
    class Form;
}

class AnimalListItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnimalListItemWidget(QWidget *parent = nullptr);

private:
    Ui::Form* ui;
};

class AnimalListWidget : public QWidget
{
    Q_OBJECT
public:
};
