#include <QDebug>
#include <QDockWidget>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "animal_edit_widget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow())
{
    ui->setupUi(this);
    ui->toolBar->addAction(QIcon(":/ui/icons/add_40.png"), "This shit", this, &MainWindow::runAnimalEditor);

}

void MainWindow::runAnimalEditor()
{
    qDebug() << Q_FUNC_INFO;
}
