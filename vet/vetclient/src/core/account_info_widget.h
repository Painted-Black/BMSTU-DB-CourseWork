#pragma once

#include <QWidget>

namespace Ui
{
    class acc_info_widget;
}

class AccountInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AccountInfoWidget(QWidget *parent = nullptr);
private:
    Ui::acc_info_widget* ui;
};

