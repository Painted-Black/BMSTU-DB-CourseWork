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
    AccessLevel l = access_data.getLevel();
    ui->input_access_label->setText(access_data.getLevel().toString());
    ui->input_name_label->setText(passport.getName());
    ui->input_surname_label->setText(passport.getSurname());
    ui->input_part_label->setText(passport.getPatronymic());
    ui->input_sex_label->setText(passport.getGender().toString());
    ui->input_birth_label->setText(passport.getBirthday().toString());
    ui->input_num_label->setText(passport.getPassport_num());
    ui->input_issue_date_label->setText(passport.getIssue_date().toString());
    ui->input_nation_label->setText(passport.getNationality());


}
