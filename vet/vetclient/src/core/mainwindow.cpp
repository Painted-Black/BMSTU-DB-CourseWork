#include <limits>
#include <QDebug>
#include <QDockWidget>
#include <QLabel>
#include <QTabBar>
#include <QDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "account_info_widget.h"
#include "animal_edit_widget.h"
#include "animal_list_item_widget.h"

enum TabType
{
	AccountWidget      = 1,
	AnimalWidget        = 2,
	EditAnimalWidget = 3
};

enum TabFlags
{
	None           = 0b00,
	Unclosable = 0b01,
	Single          = 0b10
};

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow())
{
	ui->setupUi(this);
	connect(ui->acc_action, &QAction::triggered, this, &MainWindow::accInfo);
	connect(ui->exit_action, &QAction::triggered, this, &MainWindow::exit);
	connect(ui->pet_reg, &QAction::triggered, this, &MainWindow::createNewAnimal);
	connect(ui->pet_find, &QAction::triggered, this, &MainWindow::runAnimalEditor);
	connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);

	addToolBarAction(QIcon(":/ui/icons/add_40.png"), "Животные", &MainWindow::runAnimalEditor);
}

void MainWindow::runAnimalEditor()
{
	QWidget* w = addTab(QIcon(":/ui/icons/add_user_80.png"), "Животные",
				{AnimalWidget, Single}, &MainWindow::createWidgetAnimals);
	w->show();
}

QWidget* MainWindow::addTab(
		const QIcon& icon, const QString& title,
		std::tuple<uint64_t, uint8_t> flags, InitFunc<QWidget *> init_cb)
{
	QTabBar* bar = ui->tabWidget->tabBar();
	auto fl = std::get<1>(flags);
	if (fl & Single)
	{
		auto count = bar->count();
		auto searched = std::get<0>(flags);
		for (decltype (count) i = 0; i < count; ++i)
		{
			auto data = bar->tabData(i).value<uint8_t>();
			if (searched == data)
			{
				bar->setCurrentIndex(i);
				return ui->tabWidget->widget(i);
			}
		}
	}

	QWidget* widget = new QWidget(ui->tabWidget);
	(this->*init_cb)(widget);
	int idx = ui->tabWidget->addTab(widget, icon, title);
	bar->setTabData(idx, QVariant::fromValue(fl));
	bar->setCurrentIndex(idx);
	return widget;
}

void MainWindow::createWidgetAnimals(QWidget * w)
{
	QHBoxLayout* layout = new QHBoxLayout();
	AnimalListWidget* aiw = new AnimalListWidget(w);
	connect(aiw, &AnimalListWidget::selectItem, this, &MainWindow::createWidgetAnimalInfo);

	aiw->show(QUrl("http://127.0.0.1:4446/animals/all/short"), access_data.getPassword());
	layout->addWidget(aiw);
	w->setLayout(layout);
}

void MainWindow::createWidgetAnimalInfo(uint64_t id)
{
	QTabBar* bar = ui->tabWidget->tabBar();
	QWidget* w = new QWidget(ui->tabWidget);
	QHBoxLayout* layout = new QHBoxLayout();
	AnimalEditWidget* aiw = new AnimalEditWidget(w);
	QUrl url(QString("http://127.0.0.1:4446/animals?id=%1").arg(static_cast<qulonglong>(id)));
	aiw->show(url, access_data.getPassword());
	layout->addWidget(aiw);
	w->setLayout(layout);

	int idx = ui->tabWidget->addTab(w, QIcon(":/ui/icons/user_green_80.png"), "Добавить");
	bar->setTabData(idx, QVariant::fromValue<uint8_t>(None));
	ui->tabWidget->setCurrentIndex(idx);
}

void MainWindow::createWidgetAccountInfo(QWidget * w)
{
	QHBoxLayout* layout = new QHBoxLayout();
	AccountInfoWidget* aiw = new AccountInfoWidget(w);
	aiw->setAccessData(access_data);
	aiw->show();
	layout->addWidget(aiw);
	w->setLayout(layout);
}

void MainWindow::createNewAnimal()
{
	QTabBar* bar = ui->tabWidget->tabBar();
	QWidget* w = new QWidget(ui->tabWidget);
	QHBoxLayout* layout = new QHBoxLayout();
	AnimalEditWidget* aiw = new AnimalEditWidget(w);
	layout->addWidget(aiw);
	w->setLayout(layout);

	int idx = ui->tabWidget->addTab(w, QIcon(":/ui/icons/user_green_80.png"), "Добавить");
	bar->setTabData(idx, QVariant::fromValue<uint8_t>(None));
	ui->tabWidget->setCurrentIndex(idx);
}

void MainWindow::addToolBarAction(const QIcon& icon, const QString& text, const Callback &cb)
{
	QAction* action = new QAction(icon, text, ui->toolBar);
	connect(action, &QAction::triggered, this, cb);
	ui->toolBar->addAction(action);
}

void MainWindow::closeTab(int idx)
{
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
void MainWindow::accInfo()
{
	addTab(QIcon(":/ui/icons/user_green_80.png"), "Аккаунт",
		{AccountWidget, Single}, &MainWindow::createWidgetAccountInfo);
}

void MainWindow::exit()
{
	QCoreApplication::instance()->exit(0);
}
