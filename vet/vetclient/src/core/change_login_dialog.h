#pragma once

#include <QDialog>

namespace Ui {
class ChangeLoginDialog;
}

class ChangeLoginDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ChangeLoginDialog(QWidget *parent = nullptr);
	void setOldLogin(const QString& old);
	void accept() override;
	QString getNewLogin();
	~ChangeLoginDialog();

private:
	Ui::ChangeLoginDialog *ui;
	QString new_login;
};

