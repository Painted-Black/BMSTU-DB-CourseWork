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
#include "animal_edit_widget.h"

enum TabType
{
	AccountWidget,
	AnimalWidget
};

enum TabFlags
{
	Unclosable = 0b01,
	Single          = 0b10
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
	addTab(QIcon(":/ui/icons/add_user_80.png"), "Животные", {AnimalWidget, Single});
}

void MainWindow::addTab(const QIcon& icon, const QString& title, std::tuple<uint64_t, uint8_t> flags)
{
	QTabBar* bar = ui->tabWidget->tabBar();
	auto fl = std::get<1>(flags);
	if (fl & Single)
	{
		auto count = bar->count();
		uint64_t searched = std::get<0>(flags);
		for (decltype (count) i = 0; i < count; ++i)
		{
			auto data = bar->tabData(i).value<uint8_t>();
			if (searched == data)
			{
				bar->setCurrentIndex(i);
				return;
			}
		}
	}

	int idx = bar->addTab(icon, title);
	bar->setTabData(idx, QVariant::fromValue(fl));
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

void MainWindow::accInfo()
{
}

void MainWindow::exit()
{
	qDebug() << Q_FUNC_INFO << "Exit menu action";
}
