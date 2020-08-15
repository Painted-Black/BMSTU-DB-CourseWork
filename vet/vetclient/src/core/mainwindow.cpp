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
	AccountWidget
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
}

void MainWindow::runAnimalEditor()
{
	//	qDebug() << Q_FUNC_INFO;
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
