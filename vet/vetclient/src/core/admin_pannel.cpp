#include <QNetworkRequest>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QVariant>

#include "admin_pannel.h"
#include "ui_admin_pannel.h"
#include "network/network_fetcher.h"
#include "utils/utils.h"
#include "user_info_dialog.h"
#include "question_dialog.h"
#include "utils/singlenton.h"
#include "popup.h"
#include "config/config.h"
#include "core/add_user_dialog.h"

AdminPannel::AdminPannel(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::AdminPannel()),
	model(new UsersTableModel())
{
	ui->setupUi(this);
	connect(ui->tableView, &QAbstractItemView::doubleClicked, this, &AdminPannel::tableViewDoubleClicked);
	connect(ui->add_toolButton, &QPushButton::released, this, &AdminPannel::addUserBtnClicked);
	connect(ui->delete_toolButton, &QPushButton::released, this, &AdminPannel::deleteUserBtnClicked);
}

bool AdminPannel::show(const QUrl &url, std::chrono::milliseconds tout)
{
	ui->tableView->setModel(model);
	int model_col_count = model->columnCount();
	for (int i = 0; i < model_col_count; ++i)
	{
		ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
	}

	QNetworkRequest req;
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(password));
	req.setUrl(url);

	NetworkFetcher fetcher;
	auto reply = fetcher.httpGet(req, tout);
	if (std::get<0>(reply) != 200)
	{
		qCritical() << Q_FUNC_INFO << "Invalid data" << std::get<2>(reply);
		return  false;
	}
	else
	{
		QVector<ShortUserInfo> data = deserializeArray<ShortUserInfo>(std::get<2>(reply));
		model->setTableData(data);
	}

	return true;
}

AdminPannel::~AdminPannel()
{
	delete ui;
	delete model;
}

void AdminPannel::setPassword(QByteArray pass)
{
	password = pass;
}

void AdminPannel::tableViewDoubleClicked(const QModelIndex &index)
{
	qDebug() << Q_FUNC_INFO << "Double click";
	UserInfoDialog* dialog = new UserInfoDialog(this);
	dialog->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
	dialog->show(model->dataAt(index.row()));
	if (dialog->exec() == QDialog::Accepted)
	{
		qDebug() << "Saving...";
		if (dialog->isChanged())
		{
			qDebug() << "Saving changes";
		}
		ShortUserInfo new_info = dialog->getShortUserInfo();

#pragma message "TODO"
		qDebug() << "Saved";
	}
}

void AdminPannel::addUserBtnClicked()
{
	qDebug() << "Adding user";

	AddUserDialog* dialog = new AddUserDialog(this);
	dialog->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
	if (dialog->exec() == QDialog::Accepted)
	{
#pragma message "TODO"
	}
}

void AdminPannel::deleteUserBtnClicked()
{
	qDebug() << "Deleting user";

	QItemSelectionModel *select = ui->tableView->selectionModel();
	QModelIndexList selected_rows = select->selectedRows();
	if (selected_rows.size() != 0)
	{
		int row = selected_rows.begin()->row();
		bool is_ok = deleteUser(model->dataAt(row).getUid());
		if (is_ok == true)
		{
			model->deleteAt(row);
		}
	}
}

bool AdminPannel::deleteUserQuery(uint64_t id)
{
	qDebug() << "Deleting user " << id;
	auto& cfg = Singlenton<Config>::getInstance();

	QNetworkRequest req;
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(password));
	req.setUrl(cfg.getUrlDeleteUser());
	QByteArray data = serializeAccId(id);
	NetworkFetcher fetcher;
	auto reply = fetcher.httpPost(req, data, cfg.getTimeout());
	const auto& code = std::get<0>(reply);
	const auto& body = std::get<2>(reply);
	if (code != 204)
	{
		qCritical() << Q_FUNC_INFO << "Failed request. Http code:" << code << body;
		return false;
	}
	return true;
}

bool AdminPannel::deleteUser(uint64_t id)
{
	QString question = "Удалить пользователя с id ";
	question += QVariant::fromValue(id).toString();
	question += "?";
	QuestionDialog *dia = new QuestionDialog(question, this);
	bool is_ok = false;
	if (dia->exec() == QDialog::Accepted)
	{
		is_ok = deleteUserQuery(id);
		auto& popup = Singlenton<PopUp>::getInstance();
		if (is_ok == false)
		{
			popup.setPopupText("Произошла ошибка, попробуйте еще раз.");
			popup.show();
		}
		else
		{
			popup.setPopupText("Пользователь удален.");
			popup.show();
		}
	}
	return is_ok;
}

QByteArray AdminPannel::serializeAccId(uint64_t id)
{
	QJsonObject obj;
	obj.insert("acc_id", QVariant::fromValue(id).toString());
	return QJsonDocument(obj).toJson();
}
