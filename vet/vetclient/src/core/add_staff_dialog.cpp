#include "add_staff_dialog.h"
#include "ui_add_staff_dialog.h"
#include "ui_passport.h"
#include "types/json_fields.h"
#include "core/add_shedule_item_dialog.h"
#include "types/passport.h"
#include "utils/singlenton.h"
#include "core/popup.h"
#include "config/config.h"
#include "network/network_fetcher.h"
#include "utils/utils.h"

#include <QDebug>
#include <QPushButton>
#include <QDebug>
#include <QNetworkRequest>

AddStaffDialog::AddStaffDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddStaffDialog),
	passport_w(new Ui::PassportWidget),
	model(new StaffScheduleTableModel())
{
	ui->setupUi(this);
	QDate current_date = QDate::currentDate();
	ui->empl_dateEdit->setDate(current_date);

	QHBoxLayout* passport_lay = new QHBoxLayout();
	QWidget* passport_wdg = new QWidget(this);
	passport_w->setupUi(passport_wdg);
	passport_lay->addWidget(passport_wdg);
	ui->widget->setLayout(passport_lay);
//	setFixedSize(minimumSize());
	ui->tableView->setModel(model);

	ui->edu_comboBox->addItem(RusEduLevelType::rus_edu_middle);
	ui->edu_comboBox->addItem(RusEduLevelType::rus_edu_bachelor);
	ui->edu_comboBox->addItem(RusEduLevelType::rus_edu_resident);
	ui->edu_comboBox->addItem(RusEduLevelType::rus_edu_specialist);
	ui->edu_comboBox->addItem(RusEduLevelType::rus_edu_postgraduate);
	connect(ui->add_schedule_toolButton, &QPushButton::released, this, &AddStaffDialog::addSchedule);
	connect(ui->delet_schedule_toolButton, &QPushButton::released, this, &AddStaffDialog::deleteSchedule);

	for (int i = 0; i < model->columnCount(); ++i)
	{
		ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
	}
}

AddStaffDialog::~AddStaffDialog()
{
	delete ui;
}

void AddStaffDialog::setPassword(const QByteArray &password)
{
	mPassword = password;
}

void AddStaffDialog::setPositionsList(const QVector<Position> &positionsList)
{
    mPositionsList = positionsList;
	for (const Position& p : mPositionsList)
	{
		ui->positions_comboBox->addItem(p.getTitle());
	}
}

void AddStaffDialog::accept()
{
	auto& popup = Singlenton<PopUp>::getInstance();
	QString surname = passport_w->surname_lineEdit->text();
	if (surname.isEmpty() == true)
	{
		popup.setPopupText("Фамилия не может быть пустой");
		popup.show();
		return;
	}
	QString name = passport_w->name_lineEdit->text();
	if (name.isEmpty() == true)
	{
		popup.setPopupText("Имя не может быть пустым");
		popup.show();
		return;
	}
	QString patr = passport_w->patr_lineEdit->text();
	Gender gender;
	if (passport_w->female_radioButton->isChecked())
	{
		gender.setGenderType(Gender::GenderEnum::Female);
	}
	else if (passport_w->male_radioButton->isChecked())
	{
		gender.setGenderType(Gender::GenderEnum::Male);
	}
	else
	{
		popup.setPopupText("Выберите пол");
		popup.show();
		return;
	}
	QDate birth = passport_w->birth_dateEdit->date();
	QDate issue_date = passport_w->birth_dateEdit->date();
	if (issue_date < birth)
	{
		popup.setPopupText("Паспорт был выдан раньше даты рождения?");
		popup.show();
		return;
	}
	QString num = passport_w->num_lineEdit->text();
	if (num.isEmpty() == true)
	{
		popup.setPopupText("Номер паспорта не может быть пустым");
		popup.show();
		return;
	}
	num.remove(' ');
	QString nationality = passport_w->nationality_lineEdit->text();

	Position position = mPositionsList.at(ui->positions_comboBox->currentIndex());
	EducationLevel edu_level;
	QString edu_str_lvl = ui->edu_comboBox->currentText();
	edu_level.fromString(edu_str_lvl);
	QDate empl_date = ui->empl_dateEdit->date();
	ScheduleList sched(model->getAllData());

	Passport pass;
	pass.setSurname(surname);
	pass.setName(name);
	pass.setPatronymic(patr);
	pass.setGender(gender);
	pass.setBirthday(birth);
	pass.setPassportNum(num);
	pass.setIssueDate(issue_date);
	pass.setNationality(nationality);

	Staff staff;
	staff.setPassport(pass);
	staff.setPosition(position);
	staff.setEdu_level(edu_level);
	staff.setEmploy_date(empl_date);
	staff.setShed_list(sched);

	bool is_ok = insertStaffQueryToServer(staff);
	if (is_ok == false)
	{
		return;
	}
	QDialog::accept();

}

void AddStaffDialog::addSchedule()
{
	qDebug() << Q_FUNC_INFO << "Add shed";
	AddSheduleItemDialog dialog;
	if (dialog.exec() == QDialog::Accepted)
	{
		qDebug() << "New schedule item";
		Schedule new_sched = dialog.newShedule();
		model->addData(new_sched);
	}
}

void AddStaffDialog::deleteSchedule()
{
	qDebug() << Q_FUNC_INFO << "Delete shed";
	QItemSelectionModel *select = ui->tableView->selectionModel();
	QModelIndexList selected_rows = select->selectedRows();
	if (selected_rows.size() != 0)
	{
		int row = selected_rows.begin()->row();
		qDebug() << "row" << row;
		model->removeAt(row);
	}
}

bool AddStaffDialog::insertStaffQueryToServer(const Staff &s)
{
	qDebug() << Q_FUNC_INFO << "Query";

	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest request(cfg.getUrlAddStaff());
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(mPassword));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	NetworkFetcher fetcher;

	QByteArray raw_data = toJson(s.serialize());

	auto reply = fetcher.httpPost(request, raw_data, cfg.getTimeout());
	int32_t code = std::get<0>(reply);
	auto& popup = Singlenton<PopUp>::getInstance();
	if (code == -1)
	{
		popup.setPopupText("Нет соединения с интернетом или доступа к серверу.");
		popup.show();
		return false;
	}
	if (code != 201)
	{
		popup.setPopupText("Возникла ошибка.");
		popup.show();
		return false;
	}
	// ok
	qDebug() << Q_FUNC_INFO << "Saved";
	popup.setPopupText("Данные успешно сохранены.");
	popup.show();

	return true;
}
