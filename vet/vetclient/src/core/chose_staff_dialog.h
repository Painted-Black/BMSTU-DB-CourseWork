#pragma once

#include <QDialog>

#include "user_list_item_widget.h"

namespace Ui {
class ChoseStaffDialog;
}

class ChoseStaffDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ChoseStaffDialog(QWidget *parent = nullptr);
	~ChoseStaffDialog();
	void userInfoWidget(uint64_t id);

	void setAccessData(const QByteArray &value);
	void show();

	ShortStaffInfo getStaffIinfo() const;

private:
	Ui::ChoseStaffDialog *ui;
	UserListItemWidget* uiw;
	ShortStaffInfo mInfo;

	QByteArray access_data;
};

