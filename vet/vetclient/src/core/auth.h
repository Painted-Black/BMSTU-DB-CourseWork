#pragma once

#include <QDialog>
#include "core/fetcher.h"

namespace Ui
{
    class auth_dialog;
}

class Auth : public QDialog
{
    Q_OBJECT
public:
    explicit Auth(QWidget *parent = nullptr);
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    void procLog();
    void cb_request_auth(uint32_t, std::unique_ptr<QByteArray>);
private:
    Ui::auth_dialog* ui;
    QByteArray uid;
    Fetcher::Callback cb;
    Fetcher fetcher;
};

