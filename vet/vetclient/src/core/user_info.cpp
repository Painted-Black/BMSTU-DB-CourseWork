#include "user_info.h"
#include "ui_user_info.h"

UserInfo::UserInfo(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::UserInfo)
{
	ui->setupUi(this);
}

UserInfo::~UserInfo()
{
	delete ui;
}
