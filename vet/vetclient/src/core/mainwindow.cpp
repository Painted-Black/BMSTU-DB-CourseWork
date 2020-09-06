#include <limits>
#include <QList>
#include <QDebug>
#include <QDockWidget>
#include <QLabel>
#include <QTabBar>
#include <QDialog>
#include <QScreen>
#include <QHBoxLayout>
#include <QPushButton>
#include "network/network_fetcher.h"
#include <QVariant>
#include "utils/singlenton.h"
#include "popup.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "account_info_widget.h"
#include "animal_edit_widget.h"
#include "new_visit_widget.h"
#include "animal_list_item_widget.h"
#include "config/config.h"
#include "utils/utils.h"
#include "core/main_tab_widget.h"
#include "core/admin_pannel.h"
#include "core/client_list_widget.h"
#include "core/main_vet_pannel.h"
#include "core/staff_tab_widget.h"


enum TabType
{
	AccountWidget		= 1,
	AnimalWidget		= 2,
	EditAnimalWidget	= 3,
	VisitWidget			= 4,
	MainWidget			= 5,
	AddAnimalWidget		= 6,
	StaffWidget			= 7,
	PositionsWidget		= 8
};

enum TabFlags
{
	None		   = 0b00,
	Unclosable     = 0b01,
	Single		   = 0b10
};

Q_DECLARE_METATYPE(TabType)
Q_DECLARE_METATYPE(TabFlags)

template <typename Func>
void checkAnimalWidget(QObject* sender, QTabWidget* tab, Func f)
{
	AnimalEditWidget* widget = sender->parent()->findChild<AnimalEditWidget*>();
	bool is_fill = widget->isFills();
	if (is_fill == false)
	{
		PopUp& notifier = Singlenton<PopUp>::getInstance();
		notifier.setPopupText("Не все поля были заполнены");
		notifier.show();
	}

	if (f(widget) == true)
	{
		tab->removeTab(tab->currentIndex());
	}
}

MainWindow::MainWindow(const AccessData& value, QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow())
{
	ui->setupUi(this);

	qRegisterMetaType<TabType>();
	qRegisterMetaType<TabFlags>();

	access_data = value;
	AccessLevel level = access_data.getLevel();

	if (level.isVet() == true)
	{
		qDebug() << "Vet";
		constructVet();
	}
	else if (level.isAdmin() == true)
	{
		qDebug() << "Admin";
		constructAdmin();
	}
	else if (level.isMain() == true)
	{
		qDebug() << "Main";
		constructVet();
		constructMain();
	}
	else if (level.isRegistry() == true)
	{
		qDebug() << "Registry";
		constructReistry();
	}
	else
	{
		qDebug() << "Unknown access level";
	}
	// common
	connect(ui->acc_action, &QAction::triggered, this, &MainWindow::accInfo);
	connect(ui->exit_action, &QAction::triggered, this, &MainWindow::exit);
	connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
}

void MainWindow::constructAdmin()
{
	QWidget* admin_w = addTab(QIcon(":/ui/icons/system.png"), "Настройки системы",
								{MainWidget, Unclosable}, &MainWindow::showAdminPannel);
	admin_w->show();
	ui->menu_2->menuAction()->setVisible(false);
//	ui->menu_2->setDisabled(true);
}

void MainWindow::constructVet()
{
	QWidget* w = addTab(QIcon(":/ui/icons/logo_green_80.png"), "Главная страница",
						{MainWidget, Unclosable}, &MainWindow::showMainTab);
	w->show();
	connect(ui->pet_reg, &QAction::triggered, this, &MainWindow::createWidgetNewAnimal);
	connect(ui->pet_find, &QAction::triggered, this, &MainWindow::runAnimalEditor);
	addToolBarAction(QIcon(":/ui/icons/icons8-group-of-animals-48.png"), "Животные", &MainWindow::runAnimalEditor);
	addToolBarAction(QIcon(":/ui/icons/treatment-80.png"), "Ветеринарный осмотр", &MainWindow::newVisit);
}

void MainWindow::constructReistry()
{
}

void MainWindow::constructMain()
{
	addToolBarAction(QIcon(":/ui/icons/team.png"), "Сотрудники", &MainWindow::showStaff);
	addToolBarAction(QIcon(":/ui/icons/name-tag.png"), "Должности", &MainWindow::showPositions);
}

void MainWindow::runAnimalEditor()
{
	qDebug() << Q_FUNC_INFO;

	QWidget* w = addTab(QIcon(":/ui/icons/icons8-group-of-animals-48.png"), "Животные",
				{AnimalWidget, Single}, &MainWindow::createWidgetAnimals);
	w->show();
}

void MainWindow::showStaffList(QWidget *w)
{
	qDebug() << Q_FUNC_INFO << "Staff list";

	QHBoxLayout* layout = new QHBoxLayout();
	StaffTabWidget* stw = new StaffTabWidget(w);
	stw->setObjectName("MainVetPannel");
	stw->setPassword(access_data.getPassword());
	stw->show();
	layout->addWidget(stw);
	w->setLayout(layout);
	stw->update();
}

void MainWindow::showPositionsList(QWidget *w)
{
	qDebug() << Q_FUNC_INFO << "Positions list";
	QHBoxLayout* layout = new QHBoxLayout();
	MainVetPannel* mvp = new MainVetPannel(w);
	mvp->setObjectName("MainVetPannel");
	mvp->setPassword(access_data.getPassword());
	mvp->show();
	layout->addWidget(mvp);
	w->setLayout(layout);
	mvp->update();
}

void MainWindow::showMainTab(QWidget *w)
{
	qDebug() << Q_FUNC_INFO;

	auto& cfg = Singlenton<Config>::getInstance();
	QUrl url = cfg.getUrlAnimal();

	QBoxLayout* layout = new QVBoxLayout();
	MainTabWidget* aiw = new MainTabWidget(w);
	layout->addWidget(aiw);
	w->setLayout(layout);
	aiw->show(cfg.getUrlCurrentvisits(), cfg.getTimeout(), access_data.getPassword());
	connect(aiw, &MainTabWidget::newVisit, this, &MainWindow::newVisit);
	connect(aiw, &MainTabWidget::patients, this, &MainWindow::patients);
}

void MainWindow::showAdminPannel(QWidget *w)
{
	qDebug() << Q_FUNC_INFO << "Admin`s pannel";
	auto& cfg = Singlenton<Config>::getInstance();
	QBoxLayout* layout = new QVBoxLayout();
	AdminPannel* pannel = new AdminPannel(w);
	pannel->setPassword(access_data.getPassword());
	layout->addWidget(pannel);
	w->setLayout(layout);
	pannel->show(cfg.getUrlSystemUsersList(), cfg.getTimeout());
}

void MainWindow::showStaff()
{
	qDebug() << Q_FUNC_INFO << "Show staff";
	QWidget* w = addTab(QIcon(":/ui/icons/team.png"), "Сотрудники",
				{StaffWidget, Single}, &MainWindow::showStaffList);
	w->show();
}

void MainWindow::showPositions()
{
	qDebug() << Q_FUNC_INFO << "Show Positions";
	QWidget* w = addTab(QIcon(":/ui/icons/name-tag.png"), "Должности",
				{PositionsWidget, Single}, &MainWindow::showPositionsList);
	w->show();
}

QWidget* MainWindow::addTab(
		const QIcon& icon, const QString& title,
		std::tuple<uint64_t, uint8_t> flags, InitFunc<QWidget *> init_cb)
{
	QTabBar* bar = ui->tabWidget->tabBar();

	auto srch_type = std::get<0>(flags);
	auto flg = std::get<1>(flags);
	QVariantList user_data = { QVariant::fromValue(srch_type), QVariant::fromValue(flg)};

	if (flg & Single)
	{
		auto find = findTag(std::get<0>(flags));
		if (std::get<0>(find) == true)
		{
			return std::get<1>(find);
		}
	}

	QWidget* widget = new QWidget(ui->tabWidget);
	(this->*init_cb)(widget);
	int idx = ui->tabWidget->addTab(widget, icon, title);
	bar->setTabData(idx, user_data);
	ui->tabWidget->setCurrentIndex(idx);
	return widget;
}

std::tuple<bool, QWidget *> MainWindow::findTag(uint64_t searched) const
{
	QTabBar* bar = ui->tabWidget->tabBar();
	auto count = bar->count();
	for (decltype (count) i = 0; i < count; ++i)
	{
		auto tab_data = bar->tabData(i).toList();
		if (tab_data.size() != 2)
		{
			continue;
		}

		auto data = tab_data.at(0).value<uint64_t>();
		if (searched == data)
		{
			bar->setCurrentIndex(i);
			return { true, ui->tabWidget->widget(i) };
		}
	}

	return { false, nullptr };
}

void MainWindow::createWidgetAnimals(QWidget * w)
{
	auto& cfg = Singlenton<Config>::getInstance();

	QBoxLayout* layout = new QVBoxLayout();
	AnimalListWidget* aiw = new AnimalListWidget(w);
	QPushButton* add_btn = new QPushButton(w);
	add_btn->setText("Добавить запись");

	connect(add_btn, &QPushButton::released, this, &MainWindow::createWidgetNewAnimal);
	connect(aiw, &AnimalListWidget::selectItem, this, &MainWindow::createWidgetAnimalInfo);

	aiw->show(cfg.getUrlAnimalsShortInfo(), cfg.getTimeout(), access_data.getPassword());
	layout->addWidget(aiw);
	layout->addWidget(add_btn);
	w->setLayout(layout);
}

void MainWindow::createWidgetAnimalInfo(uint64_t id)
{
	auto& cfg = Singlenton<Config>::getInstance();
	QUrl url = cfg.getUrlAnimal();
	url.setQuery(QString("id=%1").arg(static_cast<qulonglong>(id)));

	QTabBar* bar = ui->tabWidget->tabBar();
	QWidget* w = new QWidget(ui->tabWidget);
	QVBoxLayout* layout = new QVBoxLayout();
	AnimalEditWidget* aiw = new AnimalEditWidget(w);
	QPushButton* add_btn = new QPushButton(w);
	add_btn->setText("Редактировать запись");
	connect(add_btn, &QPushButton::released, this, &MainWindow::updateAnimal);

	aiw->show(url, cfg.getTimeout(), access_data.getPassword());
	layout->addWidget(aiw);
	layout->addWidget(add_btn);
	w->setLayout(layout);

	int idx = ui->tabWidget->addTab(w, QIcon(":/ui/icons/user_green_80.png"), "Редактировать");
	QVariantList data = { AddAnimalWidget, None };
	bar->setTabData(idx, data);
	ui->tabWidget->setCurrentIndex(idx);
}

void MainWindow::createWidgetAccountInfo(QWidget * w)
{
	QHBoxLayout* layout = new QHBoxLayout();
	AccountInfoWidget* aiw = new AccountInfoWidget(w);
	aiw->setObjectName("AccountInfoWidget");
	aiw->setAccessData(access_data);
	aiw->show();
	layout->addWidget(aiw);
	w->setLayout(layout);
}

void MainWindow::createWidgetNewVisit(QWidget *w)
{
	QHBoxLayout* layout = new QHBoxLayout();
	NewVisitWidget* nvw = new NewVisitWidget(w);
	nvw->setObjectName("NewVisitWidget");
	nvw->setAccessData(access_data);
	nvw->show();
	layout->addWidget(nvw);
	w->setLayout(layout);
}

void MainWindow::newVisit()
{
	qDebug() << Q_FUNC_INFO << "New visit";
	QWidget* w = addTab(QIcon(":/ui/icons/treatment-80.png"), "Ветеринарный осмотр",
				{VisitWidget, None}, &MainWindow::createWidgetNewVisit);

	NewVisitWidget* nvw = w->findChild<NewVisitWidget*>("NewVisitWidget");
	nvw->update();
}

void MainWindow::patients()
{
	qDebug() << "Patients";
	runAnimalEditor();
}

void MainWindow::createWidgetNewAnimal()
{
	auto& cfg = Singlenton<Config>::getInstance();
	auto& popup = Singlenton<PopUp>::getInstance();
	auto timeout = cfg.getTimeout();

	NetworkFetcher fetcher;
	QNetworkRequest request(cfg.getUrlClientsShortInfo());
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(access_data.getPassword()));

	auto answer = fetcher.httpGet(request, timeout);
	auto code = std::get<0>(answer);
	if (code == -1)
	{
		popup.setPopupText("Отсутствует подключение к интернету или нет доступа к серверу.");
		return popup.show();
	}
	else if (code != 200)
	{
		popup.setPopupText("Произошла ошибка, проверьте данные");
		return popup.show();
	}

	auto clients = deserializeArray<ShortInfoClient>(std::get<2>(answer));
	ClientListWidget clients_widget;
	clients_widget.setData(std::move(clients));
	clients_widget.update();
	if (clients_widget.exec() != QDialog::Accepted)
	{
		return;
	}

	QUrl client_url = cfg.getUrlClient();
	client_url.setQuery(QString("id=%1").arg(clients_widget.getSelectedClient().uid));
	request.setUrl(client_url);

	answer = fetcher.httpGet(request, timeout);
	code = std::get<0>(answer);
	if (code == -1)
	{
		popup.setPopupText("Отсутствует подключение к интернету или нет доступа к серверу.");
		return popup.show();
	}
	else if (code != 200)
	{
		popup.setPopupText("Произошла ошибка, проверьте данные");
		return popup.show();
	}

	Client client;
	client.deserialize(fromJson(std::get<2>(answer)));

	QTabBar* bar = ui->tabWidget->tabBar();
	QWidget* w = new QWidget(ui->tabWidget);
	QVBoxLayout* layout = new QVBoxLayout();
	AnimalEditWidget* aiw = new AnimalEditWidget(w);
	QPushButton* add_btn = new QPushButton(w);
	add_btn->setText("Добавить запись");
	add_btn->setPalette(palette());
	layout->addWidget(aiw);
	layout->addWidget(add_btn);
	w->setLayout(layout);
	w->show();
	connect(add_btn, &QPushButton::released, this, &MainWindow::createAnimal);

	aiw->setClientData(client);
	aiw->updateClientData();

	QVariantList data = { AddAnimalWidget, None } ;
	int idx = ui->tabWidget->addTab(w, QIcon(":/ui/icons/user_green_80.png"), "Добавить");
	bar->setTabData(idx, data);
	ui->tabWidget->setCurrentIndex(idx);
}

void MainWindow::updateAnimal()
{
	checkAnimalWidget(sender(), ui->tabWidget, [&](AnimalEditWidget* widget) -> bool
	{
		auto& cfg = Singlenton<Config>::getInstance();
		auto record = widget->getEditedAnimalMedicalRecord();
		if (compareAnimalRecordsWithoutClientInfo(record, widget->getAnimalMedicalRecord()))
		{
			return true;
		}
		else
		{
			NetworkFetcher fetcher;
			QNetworkRequest request(cfg.getUrlAddAnimal());
			request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
			request.setRawHeader("Authorization", QByteArray("Explicit: ").append(access_data.getPassword()));
			QJsonObject record_json = record.serialize();
			removeClientInfoFromAnimalRecord(record_json);
			auto reply = fetcher.httpPut(request, toJson(record_json), cfg.getTimeout());
			auto code = std::get<0>(reply);
			auto& popup = Singlenton<PopUp>::getInstance();
			if (code == -1)
			{
				popup.setPopupText("Отсутствует подключение к интернету или нет доступа к серверу.");
				popup.show();
			}
			else if (code != 201)
			{
				popup.setPopupText("Произошла ошибка, проверьте данные");
				popup.show();
			}
			else
			{
				return true;
			}
			return false;
		}
	});
}

void MainWindow::createAnimal()
{
	auto& cfg = Singlenton<Config>::getInstance();
	checkAnimalWidget(sender(), ui->tabWidget, [&](AnimalEditWidget* widget) -> bool
	{
		auto record = widget->getEditedAnimalMedicalRecord();
		QUrl url = cfg.getUrlAddAnimal();
		url.setQuery(QString("owner=%1").arg(widget->getAnimalMedicalRecord().getContract().getClient().getId()));
		NetworkFetcher fetcher;
		QNetworkRequest request(url);
		request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
		request.setRawHeader("Authorization", QByteArray("Explicit: ").append(access_data.getPassword()));
		QJsonObject record_json = record.serialize();
		removeClientInfoFromAnimalRecord(record_json);
		auto reply = fetcher.httpPost(request, toJson(record_json), cfg.getTimeout());
		auto code = std::get<0>(reply);
		auto& popup = Singlenton<PopUp>::getInstance();
		if (code == -1)
		{
			popup.setPopupText("Отсутствует подключение к интернету или нет доступа к серверу.");
			popup.show();
		}
		else if (code != 201)
		{
			popup.setPopupText("Произошла ошибка, проверьте данные");
			popup.show();
		}
		else
		{
			auto data = findTag(AnimalWidget);
			if (std::get<0>(data) == true)
			{
				auto index = fromSimpleJson(std::get<2>(reply));
				auto wgt = std::get<1>(data)->findChild<AnimalListWidget*>();
				ShortAnimalInfo animal_info;
				animal_info.setUid(index["anim_id"].toULongLong());
				animal_info.setName(record.getName());
				animal_info.setSpec(record.getSpecies());
				animal_info.setBirth(record.getBirth());
				wgt->addAnimal(animal_info);
				wgt->update();
			}
			return true;
		}
		return false;
	});
}

void MainWindow::addToolBarAction(const QIcon& icon, const QString& text, const Callback &cb)
{
	QAction* action = new QAction(icon, text, ui->toolBar);
	connect(action, &QAction::triggered, this, cb);
	ui->toolBar->addAction(action);
}

void MainWindow::closeTab(int idx)
{
	qDebug() << Q_FUNC_INFO;
	auto* tab = ui->tabWidget->tabBar();
	auto data = tab->tabData(idx).toList();
	auto flags = data.at(1).value<uint8_t>();
	if (flags & Unclosable)
	{
		return;
	}
	else
	{
		ui->tabWidget->removeTab(idx);
	}
}

void MainWindow::setAccessData(const AccessData &value)
{
	access_data = value;
}

void MainWindow::show()
{
	QRect rect = QGuiApplication::screens().first()->geometry();
	centredWidget(this, rect);
	QMainWindow::show();
}

void MainWindow::accInfo()
{
	qDebug() << Q_FUNC_INFO << "Acc Info menu action";
	QWidget* w = addTab(QIcon(":/ui/icons/user_green_80.png"), "Аккаунт",
		{AccountWidget, Single}, &MainWindow::createWidgetAccountInfo);

	AccountInfoWidget* acc = w->findChild<AccountInfoWidget*>("AccountInfoWidget");
	acc->update();
}

void MainWindow::exit()
{
	QCoreApplication::instance()->exit(0);
}
