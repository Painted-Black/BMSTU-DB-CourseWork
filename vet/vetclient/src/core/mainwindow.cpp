#include <limits>
#include <QList>
#include <QDebug>
#include <QDockWidget>
#include <QLabel>
#include <QTabBar>
#include <QDialog>
#include <QScreen>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include "network/network_fetcher.h"
#include "types/image_loader.h"
#include <QVariant>
#include "utils/singlenton.h"
#include "popup.h"
#include "ui_mainwindow.h"
#include "ui_client.h"
#include "ui_contacts.h"
#include "ui_passport.h"
#include "ui_address.h"
#include "ui_add_contract.h"
#include "mainwindow.h"
#include "account_info_widget.h"
#include "animal_edit_widget.h"
#include "new_visit_widget.h"
#include "animal_list_item_widget.h"
#include "config/config.h"
#include "utils/utils.h"
#include "core/main_tab_widget.h"
#include "core/admin_pannel.h"
#include "core/main_vet_pannel.h"
#include "core/staff_tab_widget.h"
#include "core/scheduleswidget.h"
#include "core/visits_widget.h"


enum TabType
{
	Undefined,
	AccountWidget ,
	AnimalWidget,
	EditAnimalWidget	,
	VisitWidget,
	MainWidget,
	AddAnimalWidget	,
	StaffWidget,
	PositionsWidget,
	ClientWidget,
	VisitsWidgetTab,
	SchedulesWidgetTab

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
	auto idx = tab->currentIndex();
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
		tab->removeTab(idx);
	}
}

MainWindow::MainWindow(const AccessData& value, QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow())
{
	ui->setupUi(this);

	qRegisterMetaType<TabType>();
	qRegisterMetaType<TabFlags>();

	setWindowIcon(QIcon(":/ui/icons/logo_green_80.png"));

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
		constructRegistry();
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
								{MainWidget, Unclosable | Single}, &MainWindow::showAdminTab);
	admin_w->show();
	addToolBarAction(QIcon(":/ui/icons/team.png"), "Сотрудники", &MainWindow::showStaff);
	addToolBarAction(QIcon(":/ui/icons/name-tag.png"), "Должности", &MainWindow::showPositions);
	ui->menu_2->menuAction()->setVisible(false);
//	ui->menu_2->setDisabled(true);
}

void MainWindow::constructVet()
{
	QWidget* w = addTab(QIcon(":/ui/icons/logo_green_80.png"), "Главная страница",
						{MainWidget, Unclosable | Single}, &MainWindow::showVetTab);
	w->show();
	connect(ui->pet_reg, &QAction::triggered, this, &MainWindow::createWidgetNewAnimal);
	connect(ui->pet_find, &QAction::triggered, this, &MainWindow::runAnimalEditor);
	addToolBarAction(QIcon(":/ui/icons/icons8-group-of-animals-48.png"), "Животные", &MainWindow::runAnimalEditor);
	addToolBarAction(QIcon(":/ui/icons/treatment-80.png"), "Ветеринарный осмотр", &MainWindow::newVisit);
	addToolBarAction(QIcon(":/ui/icons/visits_list.png"), "Осмотры", &MainWindow::visits);
}

void MainWindow::constructRegistry()
{
	QWidget* w = addTab(QIcon(":/ui/icons/logo_green_80.png"), "Список клиентов",
						{MainWidget, Unclosable | Single}, &MainWindow::showRegistryTab);
	w->show();

	connect(ui->pet_reg, &QAction::triggered, this, &MainWindow::createWidgetNewAnimal);
	connect(ui->pet_find, &QAction::triggered, this, &MainWindow::runAnimalEditor);
}

void MainWindow::constructMain()
{
	addToolBarAction(QIcon(":/ui/icons/team.png"), "Сотрудники", &MainWindow::showStaff);
	addToolBarAction(QIcon(":/ui/icons/name-tag.png"), "Должности", &MainWindow::showPositions);
	addToolBarAction(QIcon(":/ui/icons/schedule.png"), "Расписания", &MainWindow::showSchedules);
}

void MainWindow::runAnimalEditor()
{
	qDebug() << Q_FUNC_INFO;

	QWidget* w = addTab(QIcon(":/ui/icons/icons8-group-of-animals-48.png"), "Животные",
				{AnimalWidget, Single}, &MainWindow::createWidgetAnimals);
	w->show();
}

void MainWindow::visits()
{
	qDebug() << Q_FUNC_INFO;

	QWidget* w = addTab(QIcon(":/ui/icons/visits_list.png"), "Осмотры",
				{VisitsWidgetTab, Single}, &MainWindow::createWidgetVisits);
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
	stw->init();
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

void MainWindow::showVetTab(QWidget *w)
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

void MainWindow::showAdminTab(QWidget *w)
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

void MainWindow::showRegistryTab(QWidget *w)
{
	qDebug() << Q_FUNC_INFO << "Registry tab";
	auto& cfg = Singlenton<Config>::getInstance();
	QBoxLayout* lay = new QVBoxLayout();
	ClientListWidget* widget = new ClientListWidget(w);
	widget->requestData(cfg.getUrlClientsShortInfo(), cfg.getTimeout(), access_data.getPassword());
	widget->update();
	QPushButton* add_new = new QPushButton(w);
	add_new->setText("Добавить нового клиента");
	lay->addWidget(widget);
	lay->addWidget(add_new);
	w->setLayout(lay);
	widget->show();

	connect(widget, &ClientListWidget::selectClient, this, [&](){
		auto sndr = static_cast<ClientListWidget*>(sender());
		auto data = sndr->getSelectedClient();
		auto& cfg = Singlenton<Config>::getInstance();
		auto url_contract = cfg.getUrlClient();
		url_contract.setQuery(QString("id=%1").arg(data.uid));
		NetworkFetcher fetcher;
		QNetworkRequest req(url_contract);
		req.setRawHeader("Authorization", QByteArray("Explicit: ").append(access_data.getPassword()));
		auto res = fetcher.httpGet(req, cfg.getTimeout());
		auto code = std::get<0>(res);
		auto body = std::get<2>(res);
		if (code != 200)
		{
			qCritical() << Q_FUNC_INFO << "Failed request. Http code:"<< code << body;
			return;
		}

		Client client;
		client.deserialize(fromJson(body));

		url_contract = cfg.getUrlContract();
		url_contract.setQuery(QString("id=%1").arg(data.uid));
		req.setUrl(url_contract);
		res = fetcher.httpGet(req, cfg.getTimeout());
		code = std::get<0>(res);
		if (code != 200)
		{
			qCritical() << Q_FUNC_INFO << "Failed request. Http code:"<< code << body;
			return;
		}

		auto contracts = deserializeArray<Contract>(std::get<2>(res));
		auto wdg = addTab(QIcon(":/ui/icons/icons8-group-of-animals-48.png"), "Редактирование",
			{ ClientWidget, None }, &MainWindow::createWidgetClientEditor);
		wdg->setProperty("State", "Update");
		wdg->show();


		Contacts* contact_wdg = wdg->findChild<Contacts*>("contacts");
		for (const auto& phone : client.getPhones())
		{
			contact_wdg->addNewPhone(phone);
		}

		for (const auto& email : client.getEmails())
		{
			contact_wdg->addNewEmail(email);
		}

		for (const auto& social : client.getSocial())
		{
			contact_wdg->addNewSocialSite(social);
		}

		QMap<QString, QLineEdit*> fields;
		auto children = wdg->findChildren<QLineEdit*>();
		for (const auto& child : children)
		{
			fields[child->objectName()] = child;
		}

		wdg->setProperty("cli_id", QVariant::fromValue(client.getId()));
		const auto& addr = client.getAddress();
		wdg->setProperty("addr_id", QVariant::fromValue(addr.getId()));
		fields["flat_lineEdit"]->setText(addr.getFlat());
		fields["city_lineEdit"]->setText(addr.getCity());
		fields["country_lineEdit"]->setText(addr.getCountry());
		fields["house_lineEdit"]->setText(addr.getHouse());
		fields["street_lineEdit"]->setText(addr.getStreet());

		const auto& passport = client.getPassport();
		wdg->setProperty("pass_id", QVariant::fromValue(passport.getId()));
		fields["name_lineEdit"]->setText(passport.getName());
		fields["surname_lineEdit"]->setText(passport.getSurname());
		fields["patr_lineEdit"]->setText(passport.getPatronymic());
		fields["nationality_lineEdit"]->setText(passport.getNationality());
		fields["num_lineEdit"]->setText(passport.getPassportNum());
		wdg->setProperty("cli_id", QVariant::fromValue(data.uid));

		bool is_man = passport.getGender().getGenderType() == Gender::GenderEnum::Male;
		QString search_str = is_man ? "male_radioButton" : "female_radioButton";
		wdg->findChild<QRadioButton*>(search_str)->setChecked(true);

		auto lay = wdg->findChild<QVBoxLayout*>("verticalLayout_2");
		for (const auto& contract : contracts)
		{
			QWidget* contract_wdg = new QWidget(wdg);
			auto* ui_contract = new Ui::add_constract_widget();
			ui_contract->setupUi(contract_wdg);
			contract_wdg->setProperty("ui", QVariant::fromValue(contract.getContrId()));
			ui_contract->num_le->setText(contract.getCode());
			ui_contract->valid_to_de->setDate(contract.getValidUntil());
			ui_contract->conclusion_de->setDate(contract.getConclusionDate());
			QSize size = ui_contract->contract_groupBox->sizeHint();
			size.setHeight(size.height() + 32);
			contract_wdg->setMinimumSize(size);
			lay->addWidget(contract_wdg);
		}
	});

	connect(add_new, &QPushButton::released, this, [&]()
	{
		auto wdg = addTab(QIcon(":/ui/icons/icons8-group-of-animals-48.png"), "Новый клиент",
			{ ClientWidget, None }, &MainWindow::createWidgetClientEditor);
		wdg->setProperty("State", "New");
		wdg->show();
	});
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

void MainWindow::showSchedules()
{
	qDebug() << Q_FUNC_INFO << "Show schedules";
	QWidget* w = addTab(QIcon(":/ui/icons/schedule.png"), "Расписания",
				{SchedulesWidgetTab, Single}, &MainWindow::showSchedulesList);
	w->show();
}

void MainWindow::showSchedulesList(QWidget *w)
{
	qDebug() << Q_FUNC_INFO << "Show schedules list";

	QBoxLayout* layout = new QVBoxLayout();
	SchedulesWidget* pannel = new SchedulesWidget(w);
	pannel->setPassword(access_data.getPassword());
	pannel->init();
	layout->addWidget(pannel);
	w->setLayout(layout);
	pannel->show();
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

void MainWindow::createWidgetVisits(QWidget *w)
{
	qDebug() << Q_FUNC_INFO;

	QBoxLayout* layout = new QVBoxLayout();
	VisitsWidget* pannel = new VisitsWidget(w);
	pannel->setPassword(access_data.getPassword());
//	pannel->init();
	layout->addWidget(pannel);
	w->setLayout(layout);
	pannel->show();
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
	NewVisitWidget* nvw = new NewVisitWidget(NewVisitWidget::ADD, w);
	nvw->setObjectName("NewVisitWidget");
	nvw->setAccessData(access_data);
	nvw->show();
	layout->addWidget(nvw);
	w->setLayout(layout);
}

void MainWindow::createWidgetClientEditor(QWidget * w)
{
	QBoxLayout* lay = new QVBoxLayout();
	QWidget* root = new QWidget(w);
	Ui::client* ui_client = new Ui::client();
	ui_client->setupUi(root);
	ui_client->buttonBox->setVisible(false);

	ui_client->verticalLayout_2->removeWidget(ui_client->contact);
	Contacts* contacts = new Contacts(w);
	contacts->setObjectName("contacts");
	ui_client->verticalLayout_2->addWidget(contacts);

	Ui::address_widget* addr = new Ui::address_widget();
	addr->setupUi(ui_client->address);

	Ui::PassportWidget* pass = new Ui::PassportWidget();
	pass->setupUi(ui_client->passport);

	QPushButton* add_btn = new QPushButton(w);
	add_btn->setText("Сохранить изменения");
	ui_client->verticalLayout->addWidget(add_btn);
	lay->addWidget(root);
	w->setLayout(lay);

	connect(add_btn, &QPushButton::released, this, [&]()
	{
		QWidget* current_wdg = ui->tabWidget->currentWidget();
		saveClient(current_wdg, current_wdg->property("State").toString() == "Update");
	});
}

void MainWindow::saveClient(QWidget* wdg, bool update)
{
	Client client;
	auto client_wdg = wdg->findChild<Contacts*>();
	client.setId(wdg->property("cli_id").toULongLong());
	client.setEmails(client_wdg->getEmails());
	client.setPhones(client_wdg->getPhones());
	client.setSocial(client_wdg->getSocialSites());

	QMap<QString, QLineEdit*> fields_le;
	auto children_le = wdg->findChildren<QLineEdit*>();
	for (const auto& child : children_le)
	{
		fields_le[child->objectName()] = child;
	}

	QMap<QString, QDateEdit*> fields_de;
	auto children_de = wdg->findChildren<QDateEdit*>();
	for (const auto& child : children_de)
	{
		fields_de[child->objectName()] = child;
	}

	Address addr;
	addr.setId(wdg->property("addr_id").toULongLong());
	addr.setFlat(fields_le["flat_lineEdit"]->text());
	addr.setCity(fields_le["city_lineEdit"]->text());
	addr.setCountry(fields_le["country_lineEdit"]->text());
	addr.setHouse(fields_le["house_lineEdit"]->text());
	addr.setStreet(fields_le["street_lineEdit"]->text());
	client.setAddress(std::move(addr));

	bool is_male = wdg->findChild<QRadioButton*>("male_radioButton")->isChecked();
	Gender g;
	g.setGenderType(is_male ? Gender::GenderEnum::Male : Gender::GenderEnum::Female);

	Passport passport;
	passport.setId(wdg->property("pass_id").toULongLong());
	passport.setName(fields_le["name_lineEdit"]->text());
	passport.setSurname(fields_le["surname_lineEdit"]->text());
	passport.setPatronymic(fields_le["patr_lineEdit"]->text());
	passport.setNationality(fields_le["nationality_lineEdit"]->text());
	passport.setPassportNum(fields_le["num_lineEdit"]->text());
	passport.setGender(g);
	passport.setBirthday(fields_de["birth_dateEdit"]->date());
	passport.setIssueDate(fields_de["issue_date"]->date());
	client.setPassport(passport);

	auto auth_method = update ? &NetworkFetcher::httpPut : &NetworkFetcher::httpPost;

	Config& cfg = Singlenton<Config>::getInstance();
	NetworkFetcher fetcher;
	QNetworkRequest req(cfg.getUrlClient());
	req.setRawHeader("Authorization", QByteArray("Explicit: ").append(access_data.getPassword()));
	req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	auto reply = (fetcher.*(auth_method))(req, toJson(client.serialize()), cfg.getTimeout());
	auto code = std::get<0>(reply);
	if (code < 200 || code > 299)
	{
		qCritical() << Q_FUNC_INFO << "Request failed";
		return;
	}

	int cur_idx = ui->tabWidget->currentIndex();
	auto find = findTag(MainWidget);
	if (std::get<0>(find))
	{
		auto clients_wdg = std::get<1>(find)->findChild<ClientListWidget*>();
		clients_wdg->requestData(cfg.getUrlClientsShortInfo(), cfg.getTimeout(), access_data.getPassword());
		clients_wdg->update();
	}

	ui->tabWidget->removeTab(cur_idx);
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

	QDialog dlg;
	QLayout* lay = new QHBoxLayout(&dlg);
	ClientListWidget clients_widget;
	clients_widget.requestData(cfg.getUrlClientsShortInfo(), timeout, access_data.getPassword());
	clients_widget.update();
	QDialogButtonBox group;
	group.setOrientation(Qt::Vertical);
	group.setStandardButtons(QDialogButtonBox::Cancel);
	lay->addWidget(&clients_widget);
	lay->addWidget(&group);
	dlg.setLayout(lay);
	dlg.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	int height = static_cast<int>(clients_widget.height() * 1.5f);
	dlg.setGeometry(0, 0, clients_widget.width() + group.width(), height);
	centredWidget(&dlg, QGuiApplication::screens().first()->geometry());

	connect(&group, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
	connect(&clients_widget, &ClientListWidget::selectClient, &dlg, &QDialog::accept);

	if (dlg.exec() != QDialog::Accepted)
	{
		return;
	}

	NetworkFetcher fetcher;
	QNetworkRequest request;
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

	QUrl client_url = cfg.getUrlClient();
	client_url.setQuery(QString("id=%1").arg(clients_widget.getSelectedClient().uid));
	request.setUrl(client_url);
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
			QByteArray pass = access_data.getPassword();
			auto& popup = Singlenton<PopUp>::getInstance();

			auto img_data = Singlenton<ImageLoader>::getInstance()
						.saveFromFile(record.getRelPathToPhoto(), pass);
			if (std::get<0>(img_data) == false)
			{
				popup.setPopupText(std::get<1>(img_data));
				popup.show();
				return false;
			}

			record.setRelPathToPhoto(std::get<1>(img_data));

			NetworkFetcher fetcher;
			QNetworkRequest request(cfg.getUrlAddAnimal());
			request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
			request.setRawHeader("Authorization", QByteArray("Explicit: ").append(pass));
			QJsonObject record_json = record.serialize();
			removeClientInfoFromAnimalRecord(record_json);
			auto reply = fetcher.httpPut(request, toJson(record_json), cfg.getTimeout());
			auto code = std::get<0>(reply);
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
					wgt->show(cfg.getUrlAnimalsShortInfo(), cfg.getTimeout(), access_data.getPassword());
				}

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
		QByteArray pass = access_data.getPassword();
		auto& popup = Singlenton<PopUp>::getInstance();
		auto record = widget->getEditedAnimalMedicalRecord();

		auto img_data = Singlenton<ImageLoader>::getInstance()
					.saveFromFile(record.getRelPathToPhoto(), pass);
		if (std::get<0>(img_data) == false)
		{
			popup.setPopupText("Отсутствует подключение к интернету или нет доступа к серверу.");
			popup.show();
			return false;
		}

		record.setRelPathToPhoto(std::get<1>(img_data));

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
				wgt->show(cfg.getUrlAnimalsShortInfo(), cfg.getTimeout(), access_data.getPassword());
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
	auto& cfg = Singlenton<Config>::getInstance();
	QNetworkRequest request;
	request.setUrl(cfg.getUrlAuthication());
	request.setRawHeader("Authorization", QByteArray("Explicit: ").append(access_data.getPassword()));

	NetworkFetcher fetcher;
	auto reply = fetcher.httpDelete(request, cfg.getTimeout());
	const auto& code = std::get<0>(reply);
	const auto& body = std::get<2>(reply);
	if (code != 200)
	{
		qCritical() << Q_FUNC_INFO << "Failed request. Http code:"<< code << body;
		return;
	}
	QCoreApplication::instance()->exit(0);
}
