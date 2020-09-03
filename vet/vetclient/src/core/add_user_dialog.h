#pragma once

#include <QDialog>

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AddUserDialog(QWidget *parent = nullptr);
	~AddUserDialog();

private:
	Ui::AddUserDialog *ui;
};

