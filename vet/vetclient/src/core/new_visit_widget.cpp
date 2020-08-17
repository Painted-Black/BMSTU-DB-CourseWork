#include <QPushButton>
#include <QDebug>
#include <QDate>
#include "new_visit_widget.h"
#include "ui_visit.h"
#include "types/staff.h"
#include "types/position.h"
#include "types/passport.h"

NewVisitWidget::NewVisitWidget(QWidget *parent) : QWidget(parent), ui(new Ui::visit_widget())
{
    ui->setupUi(this);
    connect(ui->save_pushButton, SIGNAL(released()), this, SLOT(handle_save_button()));
    connect(ui->chose_animal_pushButton, SIGNAL(released()), this, SLOT(choseAnimal()));
}

void NewVisitWidget::update()
{
    const Staff& staff = access_data.getOwner();
    const Passport& pass = staff.getPassport();
    const Position& staff_pos = staff.getPosition();
    QString staff_snp = pass.getSurname() + " " + pass.getName() + " " + pass.getPatronymic();

    ui->input_specialist_label->setText(staff_pos.getTitle());
    ui->input_visit_by_label->setText(staff_snp);
}

void NewVisitWidget::handle_save_button()
{
    qDebug() << Q_FUNC_INFO << "Saving...";

    bool is_ambulatoty = ui->ambularory_checkBox->isChecked();
    QDate visit_date = QDate::fromString(ui->visit_date_dateEdit->text());
    QString histoty_disease = ui->anamnesis_lineEdit->text();

    qDebug() << Q_FUNC_INFO << "Saved";
}

void NewVisitWidget::setAccessData(const AccessData &value)
{
    access_data = value;
}

void NewVisitWidget::choseAnimal()
{
#pragma message "TODO"
}
