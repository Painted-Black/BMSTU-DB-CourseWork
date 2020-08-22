#pragma once

#include <QDialog>

#include "types/prescribings.h"
#include "types/json_fields.h"

namespace Ui {
class AddMedDialog;
}

class AddMedDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddMedDialog(QWidget *parent = nullptr);
    void accept() override;
    ~AddMedDialog();
    Medicine getMed();
private:
    Ui::AddMedDialog *ui;
    Medicine med;
};

