#include <QByteArray>
#include <QPushButton>
#include <QDebug>
#include <QKeyEvent>
#include <QNetworkReply>

#include "utlis/Singlenton.h"
#include "types/QJsonHeaders.h"
#include "ISerializable.h"
#include "auth.h"
#include "ui_auth_dialog.h"

struct AuthData : public ISerializable<QByteArray>
{
    QByteArray serialize() const override
    {
        QJsonObject obj;
        obj.insert("login", login);
        obj.insert("password", pass);
        return QJsonDocument(obj).toJson();
    }

    bool deserialize(const QByteArray &) noexcept override { return true; }

    QString login;
    QString pass;
};

Auth::Auth(QWidget *parent)
    : QDialog(parent), ui(new Ui::auth_dialog())
{
    ui->setupUi(this);
    fetcher.reset(new QNetworkAccessManager());

    connect(ui->login_button_auth, &QPushButton::clicked, this, &Auth::procLog);
    connect(fetcher.get(), &QNetworkAccessManager::finished, this, &Auth::authReply);
    ui->error_label->hide();
}

void Auth::procLog()
{
    AuthData data;
    data.login = ui->login_lineEdit_auth->text();
    data.pass = ui->password_lineEdit_auth->text();

    QNetworkRequest req(QUrl("http://127.0.0.1:4446/auth"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    fetcher->post(req, data.serialize());
}

void Auth::authReply(QNetworkReply *reply)
{
    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toULongLong() != 200)
    {
        ui->error_label->show();
    }
    else
    {
        auth_data = ProxyAuth::deserialize(reply->readAll());
        accept();
    }
}

std::tuple<Staff, AccessData, Passport, QByteArray> Auth::getAuthData() const
{
    return auth_data;
}
