#pragma once

#include <QDialog>

#include "utils/singlenton.h"
#include "popup.h"
#include "types/user_data.h"
#include "types/short_staff_info.h"

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AddUserDialog(QWidget *parent = nullptr);
	~AddUserDialog();

	void setAccessData(const QByteArray &value);

	bool getIsSuccess() const;

	ShortStaffInfo getNewStaffAccountData() const;

	AccessData getNewAccessData() const;

private:
	void accept() override;
	void hideErrorMessages();
	void choseStaff();
	bool queryToServer();

	Ui::AddUserDialog *ui;
	int64_t staff_id = -1;
	QString login;
	QString acc_lvl;
	QByteArray password;
	PopUp popup;
	AccessData data;
	ShortStaffInfo info;

	QByteArray access_data;

	bool isSuccess;
};

