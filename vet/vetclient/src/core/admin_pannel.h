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
	bool show(const QUrl &url, std::chrono::milliseconds tout, const QByteArray &pass);
	~AdminPannel();

private:
	void tableViewDoubleClicked(const QModelIndex &index);

	Ui::AdminPannel *ui;
	UsersTableModel* model;
};

