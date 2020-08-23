#include "ui_acc_info.h"
#include "account_info_widget.h"
#include "types/schedule.h"

#include <QVariant>
#include <QFormLayout>

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
    const Position& pos = staff.getPosition();
	ui->input_surname_label->setText(passport.getName());
	ui->input_name_label->setText(passport.getName());
	ui->input_part_label->setText(passport.getPatronymic());
	ui->input_sex_label->setText(passport.getGender().toString());
	ui->input_num_label->setText(passport.getPassportNum());
	ui->input_birth_label->setText(passport.getBirthday().toString(Qt::RFC2822Date));
	ui->input_issue_date_label->setText(passport.getIssueDate().toString(Qt::RFC2822Date));
	ui->input_nation_label->setText(passport.getNationality());
    ui->input_edu_level_label->setText(staff.getEdu_level().toString());
    ui->input_emloy_date_label->setText(staff.getEmploy_date().toString());
    ui->input_pos_title_label->setText(pos.getTitle());
    ui->input_salary_label->setText(QVariant(pos.getSalary()).toString());
    const ScheduleList shed = staff.getShed_list();
    int shed_size = shed.size();
    QFormLayout* lay = new QFormLayout(ui->sched_groupBox);
    for (int i = 0; i < shed_size; ++i)
    {
        const Schedule& cur = shed.at(i);
        QLabel* day_label = new QLabel(ui->sched_groupBox);
        QLabel* time_label = new QLabel(ui->sched_groupBox);
        day_label->setText(cur.getDay_of_week().toString());
        QString time = cur.getStart().toString();
        time += " -- ";
        time += cur.getEnd().toString();
        time_label->setText(time);
        QFont font = QFont();
        font.setBold(false);
        day_label->setFont(font);
        time_label->setFont(font);
        time_label->setAlignment(Qt::AlignLeft);
        lay->addRow(day_label, time_label);
    }
    ui->sched_frame->setLayout(lay);
}
