#include <limits>
#include <QList>
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

enum TabType
{
	AccountWidget = 1,
	AnimalWidget
};

enum TabFlags
{
	Unclosable = 0b01,
	Single		  = 0b10
};

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::MainWindow())
{
	ui->setupUi(this);
	connect(ui->acc_action, &QAction::triggered, this, &MainWindow::accInfo);
	connect(ui->exit_action, &QAction::triggered, this, &MainWindow::exit);
	connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
	addToolBarAction(QIcon(":/ui/icons/add_40.png"), "Животные", &MainWindow::runAnimalEditor);
}

void MainWindow::runAnimalEditor()
{
	qDebug() << Q_FUNC_INFO;
	QWidget* w = addTab(QIcon(":/ui/icons/add_user_80.png"), "Животные",
				{AnimalWidget, Single}, &MainWindow::createWidgetAnimals);

	auto* animal =
			w->findChild<AnimalEditWidget*>("AnimalEditWidget", Qt::FindDirectChildrenOnly);
	animal->update();
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
		auto count = bar->count();
		for (decltype (count) i = 0; i < count; ++i)
		{
			QVariantList user_data_i = bar->tabData(i).toList();
			if (user_data_i.count() != 2)
			{
				continue;
			}

			uint64_t srch_type_i = user_data_i.first().toULongLong();
			if (srch_type == srch_type_i)
			{
				bar->setCurrentIndex(i);
				return ui->tabWidget->widget(i);
			}
		}
	}

	QWidget* widget = new QWidget(ui->tabWidget);
	(this->*init_cb)(widget);
	int idx = ui->tabWidget->addTab(widget, icon, title);
	bar->setTabData(idx, user_data);
	ui->tabWidget->setCurrentIndex(idx);
	return widget;
}

void MainWindow::createWidgetAnimals(QWidget * w)
{
	QHBoxLayout* lay = new QHBoxLayout();
	AnimalEditWidget* animal = new AnimalEditWidget(w);
	animal->setObjectName("AnimalEditWidget");
	animal->show();
	lay->addWidget(animal);
	w->setLayout(lay);
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
	qDebug() << Q_FUNC_INFO << "Exit menu action";
}
