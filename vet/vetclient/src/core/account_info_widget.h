#pragma once

#include <QWidget>
#include <QByteArray>
#include <QNetworkAccessManager>

#include "types/staff.h"
#include "types/schedule.h"
#include "types/user_data.h"
#include "types/passport.h"

namespace Ui
{
	class acc_info_widget;
}

class AccountInfoWidget : public QWidget
{
	Q_OBJECT
public:
	explicit AccountInfoWidget(QWidget* = nullptr);

	void setAccessData(const AccessData &);
	void show();

private:
	Ui::acc_info_widget* ui;
	AccessData access_data;
};

