#pragma once

#include <QDialog>

namespace Ui
{
    class auth_dialog;
}

class Auth : public QDialog
{
    Q_OBJECT
public:
    explicit Auth(QWidget *parent = nullptr);
private:
    Ui::auth_dialog* ui;
};

