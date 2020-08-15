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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow())
{
    ui->setupUi(this);

    connect(ui->acc_action, &QAction::triggered, this, &MainWindow::accInfo);
    connect(ui->exit_action, &QAction::triggered, this, &MainWindow::exit);
}

void MainWindow::runAnimalEditor()
{
    //    qDebug() << Q_FUNC_INFO;
}

void MainWindow::accInfo()
{
    qDebug() << Q_FUNC_INFO << "Acc info menu action";
    acc_info_widget = new QDockWidget("Account", this);
    QWidget* root_wdg = new QWidget(acc_info_widget);
    QHBoxLayout* lay = new QHBoxLayout(root_wdg);
    lay->addWidget(new AccountInfoWidget(root_wdg));
    root_wdg->setLayout(lay);
    acc_info_widget->setWidget(root_wdg);
    acc_info_widget->setFeatures(QDockWidget::AllDockWidgetFeatures);
    acc_info_widget->show();
}

void MainWindow::exit()
{
    qDebug() << Q_FUNC_INFO << "Exit menu action";
}
