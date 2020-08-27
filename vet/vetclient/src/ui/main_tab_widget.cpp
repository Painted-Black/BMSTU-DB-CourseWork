#include "main_tab_widget.h"
#include "ui_main_tab_widget.h"

#include <QDebug>
#include <QIcon>

MainTabWidget::MainTabWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainTabWidget)
{
	ui->setupUi(this);
	connect(ui->new_visit_pushButton, &QPushButton::released, this, &MainTabWidget::new_visit_btn_pressed);
}

MainTabWidget::~MainTabWidget()
{
	delete ui;
}

void MainTabWidget::new_visit_btn_pressed()
{
	emit new_visit();
}
