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
#include "utils/singlenton.h"
#include "popup.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "account_info_widget.h"
#include "animal_edit_widget.h"
#include "new_visit_widget.h"
#include "animal_list_item_widget.h"
#include "config/config.h"

enum TabType
{
	AccountWidget	  = 1,
	AnimalWidget		= 2,
	EditAnimalWidget = 3,
	VisitWidget			= 4
};

enum TabFlags
{
	None		   = 0b00,
	Unclosable = 0b01,
	Single		  = 0b10
};

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow())
{
	ui->setupUi(this);
	connect(ui->acc_action, &QAction::triggered, this, &MainWindow::accInfo);
	connect(ui->exit_action, &QAction::triggered, this, &MainWindow::exit);
	connect(ui->pet_reg, &QAction::triggered, this, &MainWindow::createWidgetNewAnimal);
	connect(ui->pet_find, &QAction::triggered, this, &MainWindow::runAnimalEditor);
	connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
	addToolBarAction(QIcon(":/ui/icons/add_40.png"), "Животные", &MainWindow::runAnimalEditor);
	addToolBarAction(QIcon(":/ui/icons/treatment-80.png"), "Ветеринарный осмотр", &MainWindow::newVisit);
}

void MainWindow::runAnimalEditor()
{
	qDebug() << Q_FUNC_INFO;
	QWidget* w = addTab(QIcon(":/ui/icons/add_user_80.png"), "Животные",
				{AnimalWidget, Single}, &MainWindow::createWidgetAnimals);
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
		auto data = bar->tabData(i).value<uint8_t>();
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
	add_btn->setText("Добавить запись");
	connect(add_btn, &QPushButton::released, this, &MainWindow::addNewAnimal);

	aiw->show(url, cfg.getTimeout(), access_data.getPassword());
	layout->addWidget(aiw);
	layout->addWidget(add_btn);
	w->setLayout(layout);

	int idx = ui->tabWidget->addTab(w, QIcon(":/ui/icons/user_green_80.png"), "Добавить");
	bar->setTabData(idx, QVariant::fromValue<uint8_t>(None));
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
				{VisitWidget, Single}, &MainWindow::createWidgetNewVisit);

	NewVisitWidget* nvw = w->findChild<NewVisitWidget*>("NewVisitWidget");
	nvw->update();
}

void MainWindow::createWidgetNewAnimal()
{
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
	connect(add_btn, &QPushButton::released, this, &MainWindow::addNewAnimal);

	int idx = ui->tabWidget->addTab(w, QIcon(":/ui/icons/user_green_80.png"), "Добавить");
	bar->setTabData(idx, QVariant::fromValue<uint8_t>(None));
	ui->tabWidget->setCurrentIndex(idx);
}

void MainWindow::addNewAnimal()
{
	AnimalEditWidget* widget = sender()->parent()->findChild<AnimalEditWidget*>();
	bool is_fill = widget->isFills();
	if (is_fill == false)
	{
		PopUp& notifier = Singlenton<PopUp>::getInstance();
		notifier.setPopupText("Не все поля были заполнены");
		notifier.show();
		return;
	}

	auto record = widget->getAnimalMedicalRecort();
	auto animal_widget = findTag(AnimalWidget);
	if (std::get<0>(animal_widget) == true)
	{
		AnimalListWidget* lst = std::get<1>(animal_widget)->findChild<AnimalListWidget*>();
		lst->addAnimal();
	}
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
	auto flags = ui->tabWidget->tabBar()->tabData(idx).value<uint8_t>();
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
	int x = (rect.width() - width()) / 2;
	int y = (rect.height() - height()) / 2;

	setGeometry(x, y, width(), height());
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
