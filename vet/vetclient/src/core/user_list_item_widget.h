#pragma once

#include <QWidget>
#include <QListWidget>

#include "types/short_staff_info.h"

namespace Ui {
class UserListItemWidget;
}

class UserListItemWidget : public QWidget
{
	Q_OBJECT

public:
	explicit UserListItemWidget(QWidget *parent = nullptr);
	bool show(const QUrl& url, std::chrono::milliseconds tout, const QByteArray&pass);
	ShortStaffInfo findById(uint64_t id);
Q_SIGNALS:
	void selectItem(uint64_t);
private:
	QWidget* addWidget(const ShortStaffInfo& info);
	void selectItemWidget(QListWidgetItem*item);

	Ui::UserListItemWidget *ui;
	QListWidget* view;
	QVector <ShortStaffInfo> mData;
};

