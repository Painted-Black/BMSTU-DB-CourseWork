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

AddStaffDialog::AddStaffDialog(Type type, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::AddStaffDialog),
	passport_w(new Ui::PassportWidget),
	model(new StaffScheduleTableModel())
{
	ui->setupUi(this);
	QDate current_date = QDate::currentDate();
	ui->empl_dateEdit->setDate(current_date);
	mType = type;

	QHBoxLayout* passport_lay = new QHBoxLayout();
	QWidget* passport_wdg = new QWidget(this);
	passport_w->setupUi(passport_wdg);
	passport_lay->addWidget(passport_wdg);
	ui->widget->setLayout(passport_lay);
//	setFixedSize(minimumSize());
	ui->tableView->setModel(model);
	addEduLevels();

	connect(ui->add_schedule_toolButton, &QPushButton::released, this, &AddStaffDialog::addSchedule);
	connect(ui->delet_schedule_toolButton, &QPushButton::released, this, &AddStaffDialog::deleteSchedule);
	connect(ui->cancel_pushButton, &QPushButton::released, this, &QDialog::reject);

	if (mType == ADD)
	{
		connect(ui->save_pushButton, &QPushButton::released, this, &AddStaffDialog::save_new);
	}
	else
	{
		connect(ui->save_pushButton, &QPushButton::released, this, &AddStaffDialog::update);
		setWindowTitle("Редактирование сотрудника");
	}

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

void AddStaffDialog::setEditableStaff(Staff staff)
{
	mEditable = staff;
	mEditable.setShed_list(getSchedule(staff.getId()));
	ScheduleList l = mEditable.getShed_list();
	QVector<Schedule> v = l.getShedule_list();
	model->setTableData(v);
	Passport pass = staff.getPassport();
	passport_w->surname_lineEdit->setText(pass.getSurname());
	passport_w->name_lineEdit->setText(pass.getName());
	passport_w->patr_lineEdit->setText(pass.getPatronymic());
	if (pass.getGender().getGenderType() == Gender::GenderEnum::Male)
	{
		passport_w->female_radioButton->setChecked(false);
		passport_w->male_radioButton->setChecked(true);
	}
	else if (pass.getGender().getGenderType() == Gender::GenderEnum::Female)
	{
		passport_w->male_radioButton->setChecked(false);
		passport_w->female_radioButton->setChecked(true);
	}
	passport_w->birth_dateEdit->setDate(pass.getBirthday());
	passport_w->num_lineEdit->setText(pass.getPassportNum());
	passport_w->issue_date->setDate(pass.getIssueDate());
	passport_w->nationality_lineEdit->setText(pass.getNationality());
	ui->edu_comboBox->setCurrentIndex(findEduIndex(staff.getEdu_level().toString()));

	Position pos = staff.getPosition();
	ui->positions_comboBox->setCurrentIndex(findPositionIndex(pos.getTitle()));
	ui->empl_dateEdit->setDate(staff.getEmploy_date());
	passport_w->birth_dateEdit->setEnabled(false);
	ui->empl_dateEdit->setEnabled(false);
}

void AddStaffDialog::readOnly()
{
	passport_w->surname_lineEdit->setEnabled(false);
	passport_w->name_lineEdit->setEnabled(false);
	passport_w->patr_lineEdit->setEnabled(false);
	passport_w->male_radioButton->setEnabled(false);
	passport_w->female_radioButton->setEnabled(false);
	passport_w->birth_dateEdit->setEnabled(false);
	passport_w->num_lineEdit->setEnabled(false);
	passport_w->issue_date->setEnabled(false);
	passport_w->nationality_lineEdit->setEnabled(false);
	ui->positions_comboBox->setEnabled(false);
	ui->edu_comboBox->setEnabled(false);
	ui->empl_dateEdit->setEnabled(false);
	ui->save_pushButton->hide();
	ui->add_schedule_toolButton->hide();
	ui->delet_schedule_toolButton->hide();
}

void AddStaffDialog::save_new()
{
	auto& popup = Singlenton<PopUp>::getInstance();
	QString name = passport_w->name_lineEdit->text();
	if (name.isEmpty() == true)
	{
		popup.setPopupText("Имя не может быть пустым");
		popup.show();
		return;
	}
	QString surname = passport_w->surname_lineEdit->text();
	if (surname.isEmpty() == true)
	{
		popup.setPopupText("Фамилия не может быть пустой");
//		popup.setParent(this);
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

void AddStaffDialog::update()
{
	qDebug() << Q_FUNC_INFO << "updating";

	auto& popup = Singlenton<PopUp>::getInstance();
	Passport newPass;
	newPass.setId(mEditable.getPassport().getId());
	newPass.setName(passport_w->name_lineEdit->text());
	newPass.setSurname(passport_w->surname_lineEdit->text());
	newPass.setPatronymic(passport_w->patr_lineEdit->text());
	Gender g;
	if (passport_w->male_radioButton->isChecked() == true)
	{
		g.setGenderType(Gender::GenderEnum::Male);
	}
	else if (passport_w->female_radioButton->isChecked() == true)
	{
		g.setGenderType(Gender::GenderEnum::Female);
	}
	else
	{
		popup.setPopupText("Необходимо указать пол");
		popup.show();
		return;
	}
	newPass.setBirthday(mEditable.getPassport().getBirthday());
	newPass.setIssueDate(passport_w->issue_date->date());
	QString num = passport_w->num_lineEdit->text().remove(" ");
	newPass.setPassportNum(num);
	newPass.setNationality(passport_w->nationality_lineEdit->text());
	newPass.setGender(g);

	Position newPosition = mPositionsList.at(ui->positions_comboBox->currentIndex());
	Staff newStaff;
	newStaff.setId(mEditable.getId());
	EducationLevel edu_level;
	QString edu_str_lvl = ui->edu_comboBox->currentText();
	edu_level.fromString(edu_str_lvl);
	newStaff.setEdu_level(edu_level);
	newStaff.setPosition(newPosition);

	ScheduleList sched(model->getAllData());

	if (mEditable.getPosition() !=  newPosition || mEditable.getEdu_level() != edu_level)
	{
		qDebug() << "Updating staff";
		qDebug() << "Updating passport";
		bool is_ok = updateStaffQuery(newStaff);
		if (is_ok == false)
		{
			return;
		}
	}
	if (newPass != mEditable.getPassport())
	{
		qDebug() << "Updating passport";
		bool is_ok = updatePassportQuery(newPass);
		if (is_ok == false)
		{
			return;
		}
	}
	if (sched != mEditable.getShed_list())
	{
		qDebug() << "Updating schedule";
		bool is_ok = updateScheduleQuery(sched, newStaff.getId());
		if (is_ok == false)
		{
			return;
		}
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

	auto& popup = Singlenton<PopUp>::getInstance();
	auto reply = fetcher.httpPost(request, raw_data, cfg.getTimeout());
	int32_t code = std::get<0>(reply);
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

int AddStaffDialog::findPositionIndex(QString title)
{
	int size = mPositionsList.size();
	int idx = -1;
	for (int i = 0; i < size; ++i)
	{
		if (mPositionsList.at(i).getTitle() == title)
		{
			idx = i;
			break;
		}
	}
	return idx;
}

void AddStaffDialog::addEduLevels()
{
	ui->edu_comboBox->addItem(RusEduLevelType::rus_edu_middle);
	ui->edu_comboBox->addItem(RusEduLevelType::rus_edu_bachelor);
	ui->edu_comboBox->addItem(RusEduLevelType::rus_edu_resident);
	ui->edu_comboBox->addItem(RusEduLevelType::rus_edu_specialist);
	ui->edu_comboBox->addItem(RusEduLevelType::rus_edu_postgraduate);
}

int AddStaffDialog::findEduIndex(QString edu)
{
	int idx = -1;
	if (edu == RusEduLevelType::rus_edu_middle)
	{
		idx = 0;
	}
	else if (edu == RusEduLevelType::rus_edu_bachelor)
	{
		idx = 1;
	}
	else if (edu == RusEduLevelType::rus_edu_resident)
	{
		idx = 2;
	}
	else if (edu == RusEduLevelType::rus_edu_specialist)
	{
		idx = 3;
	}
	else if (edu == RusEduLevelType::rus_edu_postgraduate)
	{
		idx = 4;
	}
	return idx;
}

ScheduleList AddStaffDialog::getSchedule(uint64_t staff_id)
{
	qDebug() << Q_FUNC_INFO << "Query";

	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest request(cfg.getUrlScheduleStaff());
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(mPassword));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	NetworkFetcher fetcher;

	QByteArray raw_data = toJson(serializeId(staff_id));

	auto reply = fetcher.httpPost(request, raw_data, cfg.getTimeout());
	int32_t code = std::get<0>(reply);
	auto& popup = Singlenton<PopUp>::getInstance();
	if (code == -1)
	{
		popup.setPopupText("Нет соединения с интернетом или доступа к серверу.");
		popup.show();
	}
	if (code != 200)
	{
		popup.setPopupText("Возникла ошибка.");
		popup.show();
	}
	// ok
	QVector<Schedule> data = deserializeArray<Schedule>(std::get<2>(reply));
	ScheduleList list(data);
	return list;
}

QJsonObject AddStaffDialog::serializeId(uint64_t staff_id)
{
	QJsonObject root_obj;
	root_obj.insert(StaffJson::field_staff_id, QJsonValue::fromVariant(QVariant::fromValue(staff_id)));
	return root_obj;
}

bool AddStaffDialog::updatePassportQuery(const Passport &new_pass)
{
	auto& cfg = Singlenton<Config>::getInstance();
	QUrl url = cfg.getUrlUpdateStaff();
	url.setQuery(QString("type=%1").arg("passport"));
	QNetworkRequest request(url);
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(mPassword));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	NetworkFetcher fetcher;

	QByteArray raw_data = toJson(new_pass.serialize());

	auto& popup = Singlenton<PopUp>::getInstance();
	auto reply = fetcher.httpPut(request, raw_data, cfg.getTimeout());
	int32_t code = std::get<0>(reply);
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

bool AddStaffDialog::updateScheduleQuery(const ScheduleList &new_list, uint64_t staff_id)
{
	auto& cfg = Singlenton<Config>::getInstance();
	QUrl url = cfg.getUrlUpdateStaff();
	url.setQuery(QString("type=%1").arg("schedule"));
	QNetworkRequest request(url);
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(mPassword));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	NetworkFetcher fetcher;

	QByteArray raw_data = deserializeSchedule(new_list, staff_id);

	auto& popup = Singlenton<PopUp>::getInstance();
	auto reply = fetcher.httpPut(request, raw_data, cfg.getTimeout());
	int32_t code = std::get<0>(reply);
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

bool AddStaffDialog::updateStaffQuery(const Staff &new_staff)
{
	auto& cfg = Singlenton<Config>::getInstance();
	QUrl url = cfg.getUrlUpdateStaff();
	url.setQuery(QString("type=%1").arg("staff"));
	QNetworkRequest request(url);
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(mPassword));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	NetworkFetcher fetcher;

	QByteArray raw_data = deserializeStaff(new_staff);

	auto& popup = Singlenton<PopUp>::getInstance();
	auto reply = fetcher.httpPut(request, raw_data, cfg.getTimeout());
	int32_t code = std::get<0>(reply);
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

QByteArray AddStaffDialog::deserializeSchedule(const ScheduleList &new_list, uint64_t staff_id)
{
	QByteArray array;
	QJsonObject root_obj;
	root_obj.insert(ScheduleJson::field_shed_employee_id, QJsonValue::fromVariant(QVariant::fromValue(staff_id)));
	root_obj.insert("schedule", new_list.serialize());
	return toJson(root_obj);
}

QByteArray AddStaffDialog::deserializeStaff(const Staff &s)
{
	QByteArray array;
	QJsonObject root_obj;
	root_obj.insert(StaffJson::field_staff_id, QJsonValue::fromVariant(QVariant::fromValue(s.getId())));
	root_obj.insert(StaffJson::field_staff_edu_level, s.getEdu_level().toEngString());
	root_obj.insert(StaffJson::field_staff_position, QJsonValue::fromVariant(QVariant::fromValue(s.getPosition().getId())));
	return toJson(root_obj);
}
