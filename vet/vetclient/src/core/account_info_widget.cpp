#include "ui_acc_info.h"
#include "account_info_widget.h"

AccountInfoWidget::AccountInfoWidget(QWidget *parent)
	: QWidget(parent), ui(new Ui::acc_info_widget())
{
	ui->setupUi(this);
}

void AccountInfoWidget::setAccessData(const AccessData &value)
{
	access_data = value;
}

void AccountInfoWidget::update()
{
	ui->input_login_label->setText(access_data.getLogin());
	ui->input_access_label->setText(access_data.getLevel().toString());
	const Staff& staff = access_data.getOwner();
	const Passport& passport = staff.getPassport();
	ui->input_surname_label->setText(passport.getName());
	ui->input_name_label->setText(passport.getName());
	ui->input_part_label->setText(passport.getPatronymic());
	ui->input_sex_label->setText(passport.getGender().toString());
	ui->input_num_label->setText(passport.getPassportNum());
	ui->input_birth_label->setText(passport.getBirthday().toString(Qt::RFC2822Date));
	ui->input_issue_date_label->setText(passport.getIssueDate().toString(Qt::RFC2822Date));
	ui->input_nation_label->setText(passport.getNationality());
}
