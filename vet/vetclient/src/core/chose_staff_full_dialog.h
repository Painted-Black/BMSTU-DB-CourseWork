#pragma once

#include <QDialog>

#include "types/short_staff_info.h"

namespace Ui {
class ChoseStaffFullDialog;
}

class ChoseStaffFullDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ChoseStaffFullDialog(QWidget *parent = nullptr);
	~ChoseStaffFullDialog();
	void setPassword(const QByteArray& pass);
	void show(const ShortStaffInfo& user_info);

private:
	Ui::ChoseStaffFullDialog *ui;
	QByteArray password;
//	ShortUserInfo info;
};

