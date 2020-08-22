#pragma once

#include <QWidget>

namespace Ui {
class prescribings_widget;
}

class prescribings_widget : public QWidget
{
    Q_OBJECT

public:
    explicit prescribings_widget(QWidget *parent = nullptr);
    ~prescribings_widget();

private:
    Ui::prescribings_widget *ui;
};

