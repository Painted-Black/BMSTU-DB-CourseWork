#include "ui_acc_info.h"
#include "account_info_widget.h"

AccountInfoWidget::AccountInfoWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::acc_info_widget())
{
    ui->setupUi(this);
}

void AccountInfoWidget::setStaff(const Staff &value)
{
    staff = value;
}

void AccountInfoWidget::setAccess_data(const AccessData &value)
{
    access_data = value;
}

void AccountInfoWidget::setPassport(const Passport &value)
{
    passport = value;
}

void AccountInfoWidget::setKey(const QByteArray &value)
{
    key = value;
}

void AccountInfoWidget::show()
{
    ui->input_login_label->setText(access_data.getLogin());
    ui->input_access_label->setText(access_data.getLevel().toString());
    ui->input_name_label->setText(passport.getName());
}
