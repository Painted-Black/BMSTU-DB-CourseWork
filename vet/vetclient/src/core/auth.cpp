#include <QByteArray>
#include <QPushButton>
#include <QDebug>
#include <QKeyEvent>

#include "config/config.h"
#include "utils/singlenton.h"
#include "utils/utils.h"
#include "types/QJsonHeaders.h"
#include "iserializable.h"
#include "auth.h"
#include "ui_auth_dialog.h"
#include "core/network/network_fetcher.h"

struct AuthData : public ISerializable<QByteArray>
{
	virtual ~AuthData() noexcept override {}
	virtual QByteArray serialize() const override
	{
		QJsonObject obj;
		obj.insert("login", login);
		obj.insert("password", pass);
		return QJsonDocument(obj).toJson();
	}

	QString login;
	QString pass;
};

Auth::Auth(QWidget *parent)
	: QDialog(parent), ui(new Ui::auth_dialog())
{
	ui->setupUi(this);

	connect(ui->login_button_auth, &QPushButton::clicked, this, &Auth::procLog);
	ui->error_label->hide();
}

void Auth::procLog()
{
	AuthData data;
	data.login = ui->login_lineEdit_auth->text();
	data.pass = ui->password_lineEdit_auth->text();

	auto& cfg = Singlenton<Config>::getInstance();

	QNetworkRequest req(cfg.getUrlAuthication());
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	NetworkFetcher fetcher;
	auto responce = fetcher.httpPost(req, data.serialize(), cfg.getTimeout());
	auto code = std::get<0>(responce);
	if (code == -1)
	{
		ui->error_label->setText("Отсутстует подключение к интернету");
		ui->error_label->show();
	}
	else if (code != 200)
	{
		ui->error_label->setText("Неверный логин/пароль");
		ui->error_label->show();
	}
	else
	{
		ui->error_label->hide();
		auth_data.deserialize(fromJson(std::get<2>(responce)));
		accept();
	}
}

const AccessData& Auth::getAuthData() const
{
	return auth_data;
}
