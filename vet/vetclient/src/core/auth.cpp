#include <QByteArray>
#include <QPushButton>
#include <QDebug>
#include <QKeyEvent>

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

void cb_request_auth(uint32_t, QByteArray);

Auth::Auth(QWidget *parent)
    : QDialog(parent), ui(new Ui::auth_dialog())
{
    ui->setupUi(this);
    connect(ui->login_button_auth, &QPushButton::clicked, this, &Auth::procLog);
    ui->error_label->hide();
}

void Auth::keyPressEvent(QKeyEvent *event)
{
    QDialog::keyPressEvent(event);
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        procLog();
    }
}

void Auth::procLog()
{
    AuthData data;
    data.login = ui->login_lineEdit_auth->text();
    data.pass = ui->password_lineEdit_auth->text();

    QNetworkRequest req(QUrl("http://127.0.0.1:4446/auth"));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "Application/json");

    cb = std::bind(&Auth::cb_request_auth, this, std::placeholders::_1, std::placeholders::_2);
    fetcher.httpPost(req, data.serialize(), cb);
}

void Auth::cb_request_auth(uint32_t code, std::unique_ptr<QByteArray> data)
{
    if (code != 200)
    {
        ui->error_label->show();
    }
    else
    {
        auth_data = ProxyAuth::deserialize(*data);
        accept();
    }
}

std::tuple<Staff, AccessData, Passport, QByteArray> Auth::getAuthData() const
{
    return auth_data;
}
