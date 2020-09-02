#pragma once

#include <QDialog>

#include "types/short_user_info.h"

namespace Ui {
class UserInfoDialog;
}

class UserInfoDialog : public QDialog
{
	Q_OBJECT

public:
	explicit UserInfoDialog(QWidget *parent = nullptr);
	~UserInfoDialog();
	void show(ShortUserInfo info);
	bool isChanged();
	ShortUserInfo getShortUserInfo();

private:
	Ui::UserInfoDialog *ui;
	ShortUserInfo mData;

	QString newLogin;
	bool changed = false;
	QByteArray newPassword;
	QString newAccessLevel;

	void changeLoginBtn();
	void changePasswordBtn();
	void changeAccessLevel();
	void cancel();
	void save();
};

