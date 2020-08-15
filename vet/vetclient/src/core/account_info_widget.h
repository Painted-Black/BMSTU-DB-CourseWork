#pragma once

#include <QWidget>
#include <QByteArray>
#include <QNetworkAccessManager>

#include "types/staff.h"
#include "types/shedule.h"
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
    explicit AccountInfoWidget(QWidget *parent = nullptr);

    void setStaff(const Staff &value);
    void setAccess_data(const AccessData &value);
    void setPassport(const Passport &value);
    void setKey(const QByteArray &value);
    void show();

private:
    Ui::acc_info_widget* ui;
    Staff staff;
    AccessData access_data;
    Passport passport;
    QByteArray key;
    Shedule shedule;
};

