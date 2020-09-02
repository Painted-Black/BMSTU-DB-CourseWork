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

bool AdminPannel::show(const QUrl &url, std::chrono::milliseconds tout, const QByteArray &pass)
{
	ui->tableView->setModel(model);
	int model_col_count = model->columnCount();
	for (int i = 0; i < model_col_count; ++i)
	{
		ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
	}

	QNetworkRequest req;
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(pass));
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

void AdminPannel::tableViewDoubleClicked(const QModelIndex &index)
{
	qDebug() << Q_FUNC_INFO << "Double click";
	UserInfoDialog* dialog = new UserInfoDialog(this);
	dialog->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
	dialog->show(model->dataAt(index.row()));
	if (dialog->exec() == QDialog::Accepted)
	{
		qDebug() << "Saving...";
		ShortUserInfo new_info = dialog->getShortUserInfo();

#pragma message "TODO"
		qDebug() << "Saved";
	}
}

void AdminPannel::addUserBtnClicked()
{
	qDebug() << "Adding user";
}

void AdminPannel::deleteUserBtnClicked()
{
	qDebug() << "Deleting user";

	QItemSelectionModel *select = ui->tableView->selectionModel();
	QModelIndexList selected_rows = select->selectedRows();
	if (selected_rows.size() != 0)
	{
		int i = selected_rows.begin()->row();
		deleteUser(model->dataAt(i).getUid());
	}
}

bool AdminPannel::deleteUserQuery(uint64_t id)
{
	qDebug() << "Deleting user " << id;
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
