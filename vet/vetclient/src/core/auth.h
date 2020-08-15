#pragma once

#include <QDialog>
#include <QNetworkAccessManager>
#include "core/fetcher.h"
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

    std::tuple<Staff, AccessData, Passport, QByteArray> getAuthData() const;

private:
    void procLog();
    void authReply(QNetworkReply*);
private:
    Ui::auth_dialog* ui;
    std::tuple<Staff, AccessData, Passport, QByteArray> auth_data;
    std::unique_ptr<QNetworkAccessManager> fetcher;
};

