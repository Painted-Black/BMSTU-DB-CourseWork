#pragma once

#include <memory>
#include <QDialog>
#include "types/proxy_auth.h"

namespace Ui
{
	class auth_dialog;
}

class Auth : public QDialog
{
	Q_OBJECT
public:
	explicit Auth(QWidget *parent = nullptr);

	const AccessData &getAuthData() const;

private:
	void procLog();
private:
	Ui::auth_dialog* ui;
	AccessData auth_data;
};

