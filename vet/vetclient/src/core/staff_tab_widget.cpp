#include "staff_tab_widget.h"
#include "ui_staff_tab_widget.h"
#include "utils/singlenton.h"
#include "core/popup.h"
#include "network/network_fetcher.h"
#include "config/config.h"
#include "utils/utils.h"
#include "core/fire_dialog.h"
#include "core/add_staff_dialog.h"

#include <QNetworkAccessManager>
#include <QDebug>
#include <QPushButton>

StaffTabWidget::StaffTabWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::StaffTabWidget),
	model(new StaffTableModel())
{
	ui->setupUi(this);

	connect(ui->add_staff_toolButton, &QPushButton::released, this, &StaffTabWidget::addStaffBtn);
	connect(ui->delete_staff_toolButton, &QPushButton::released, this, &StaffTabWidget::removeStaffBtn);
	connect(ui->tableView, &QAbstractItemView::doubleClicked, this, &StaffTabWidget::tableViewDoubleClicked);
	ui->show_fired_checkBox->setChecked(true);
	connect(ui->show_fired_checkBox, &QCheckBox::stateChanged, this, &StaffTabWidget::checked);
}

StaffTabWidget::~StaffTabWidget()
{
	delete ui;
}

void StaffTabWidget::setPassword(const QByteArray &password)
{
	mPassword = password;
}

void StaffTabWidget::init()
{
	update();
	ui->tableView->setModel(model);
	int model_col_count = model->columnCount();
	for (int i = 0; i < model_col_count; ++i)
	{
		ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
	}
}

void StaffTabWidget::update()
{
	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest req;
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(mPassword));
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	req.setUrl(cfg.getUrlStaffFullInfo());

	NetworkFetcher fetcher;
	auto reply = fetcher.httpGet(req, cfg.getTimeout());
	auto code = std::get<0>(reply);
	const auto& body = std::get<2>(reply);
	if (code != 200)
	{
		qCritical() << Q_FUNC_INFO << "Invalid data" << body;
	}
	else
	{
		QVector<Staff> staff_info = deserializeArray<Staff>(body);
		model->setTableData(staff_info);
	}
}

void StaffTabWidget::tableViewDoubleClicked(const QModelIndex &index)
{
	qDebug() << "Position double clicked" << " row: " << index.row();
	QVector<Position> positions_list;
	bool is_ok = getPositionsList(&positions_list);
	if (is_ok == false)
	{
		auto& popup = Singlenton<PopUp>::getInstance();
		popup.setPopupText("Возникла ошибка, попробуйте еще раз");
		popup.show();
		return;
	}
	AddStaffDialog dialog(AddStaffDialog::EDIT);
	dialog.setPassword(mPassword);
	dialog.setPositionsList(positions_list);
	Staff s = model->dataAt(index.row());
	dialog.setEditableStaff(s);
	if (s.getFire_date().isValid() == true)
	{
		dialog.readOnly();
	}
	if (dialog.exec() == QDialog::Accepted)
	{
		qDebug() << "Updating staff table with new staff";
		this->update();
	}
}

void StaffTabWidget::addStaffBtn()
{
	qDebug() << Q_FUNC_INFO << "Add staff";
	QVector<Position> positions_list;
	bool is_ok = getPositionsList(&positions_list);
	if (is_ok == false)
	{
		auto& popup = Singlenton<PopUp>::getInstance();
		popup.setPopupText("Возникла ошибка, попробуйте еще раз");
		popup.show();
		return;
	}
	AddStaffDialog dialog;
	dialog.setPassword(mPassword);
	dialog.setPositionsList(positions_list);
	if (dialog.exec() == QDialog::Accepted)
	{
		qDebug() << "Updating staff table with new staff";
		this->update();
	}
}

void StaffTabWidget::removeStaffBtn()
{
	qDebug() << Q_FUNC_INFO << "Remove staff";

	QItemSelectionModel *select = ui->tableView->selectionModel();
	QModelIndexList selected_rows = select->selectedRows();
	if (selected_rows.size() != 0)
	{
		int row = selected_rows.begin()->row();
		if (model->dataAt(row).getFire_date().isValid() == true)
		{
			auto& popup = Singlenton<PopUp>::getInstance();
			popup.setPopupText("Сотрудник уже уволен");
			popup.show();
			return;
		}

		FireDialog* dialog = new FireDialog(this);
		if (dialog->exec() == QDialog::Accepted)
		{
			QDate fire_date = dialog->getFireDate();
			Staff fired_staff = model->dataAt(row);
			fired_staff.setFire_date(fire_date);
			bool is_ok = fireQueryToServer(fired_staff);
			if (is_ok == true)
			{
				model->setDataAt(row, fired_staff);
			}
		}
	}
}

bool StaffTabWidget::fireQueryToServer(Staff fired_staff)
{
	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest request(cfg.getUrlFireStaff());
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(mPassword));
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	NetworkFetcher fetcher;

	QByteArray raw_data = toJson(fired_staff.serialize());

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

void StaffTabWidget::checked()
{
	qDebug() << "Checked";

	if (ui->show_fired_checkBox->isChecked() == true)
	{
		model->showAll();
	}
	else
	{
		model->showOnlyEmployed();
	}
}

bool StaffTabWidget::getPositionsList(QVector<Position>* positions)
{
	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest req;
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(mPassword));
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	req.setUrl(cfg.getUrlAllPositions());

	NetworkFetcher fetcher;
	auto reply = fetcher.httpGet(req, cfg.getTimeout());
	if (std::get<0>(reply) != 200)
	{
		qCritical() << Q_FUNC_INFO << "Invalid data" << std::get<2>(reply);
		return false;
	}
	else
	{
		*positions = deserializeArray<Position>(std::get<2>(reply));
	}
	return true;
}
