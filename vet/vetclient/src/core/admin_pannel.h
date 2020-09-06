#pragma once

#include <QWidget>

#include "model/users_table_model.h"
#include "types/short_user_info.h"

namespace Ui {
class AdminPannel;
}

class AdminPannel : public QWidget
{
	Q_OBJECT

public:
	explicit AdminPannel(QWidget *parent = nullptr);
	bool show(const QUrl &url, std::chrono::milliseconds tout);
	~AdminPannel();
	void setPassword(QByteArray pass);

private:
	void tableViewDoubleClicked(const QModelIndex &index);
	void addUserBtnClicked();
	void deleteUserBtnClicked();
	bool deleteUserQuery(uint64_t id);
	bool deleteUser(uint64_t id);
	QByteArray serializeAccId(uint64_t id);

	Ui::AdminPannel *ui;
	UsersTableModel* model;
	QByteArray password;
};

