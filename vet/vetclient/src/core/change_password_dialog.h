#pragma once

#include <QDialog>

namespace Ui {
class ChangePasswordDialog;
}

class ChangePasswordDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ChangePasswordDialog(QWidget *parent = nullptr);
	~ChangePasswordDialog();
	void accept() override;
	void setOld(const QByteArray &value);

	QByteArray getNewPassword() const;

private:
	Ui::ChangePasswordDialog *ui;
	QByteArray newPassword;
};

