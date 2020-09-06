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
	ShortUserInfo getShortUserInfo();

	void setPassword(const QByteArray &value);
	bool getLoginChanged() const;
	bool getPassChanged() const;
	bool getLvlChanged() const;
	bool isChanged() const;

	ShortUserInfo getNewAccessData() const;
	QString getNewLogin() const;
	QByteArray getNewPassword() const;
	QString getNewAccessLevel() const;

private:
	QByteArray serializeAccessData();

	Ui::UserInfoDialog *ui;
	ShortUserInfo mData;
	QByteArray password;

	QString newLogin;
	bool loginChanged = false;
	QByteArray newPassword;
	bool passChanged = false;
	QString newAccessLevel;
	bool lvlChanged = false;

	void changeLoginBtn();
	void changePasswordBtn();
	void changeAccessLevel();
	void cancel();
	void save();
};

