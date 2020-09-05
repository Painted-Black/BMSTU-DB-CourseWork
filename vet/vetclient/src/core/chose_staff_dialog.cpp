#include "chose_staff_dialog.h"
#include "ui_chose_staff_dialog.h"
#include "utils/singlenton.h"
#include "config/config.h"
#include "chose_staff_full_dialog.h"

#include <QHBoxLayout>

ChoseStaffDialog::ChoseStaffDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ChoseStaffDialog),
	uiw(new UserListItemWidget(this))
{
	ui->setupUi(this);

	connect(uiw, &UserListItemWidget::selectItem, this, &ChoseStaffDialog::userInfoWidget);
	QBoxLayout* layout = new QVBoxLayout();
	layout->addWidget(uiw);
	ui->main_widget->setLayout(layout);
}

ChoseStaffDialog::~ChoseStaffDialog()
{
	delete ui;
}

void ChoseStaffDialog::userInfoWidget(uint64_t id)
{
	ChoseStaffFullDialog * dia = new ChoseStaffFullDialog(this);
	dia->setPassword(access_data);
	ShortStaffInfo staff = uiw->dataAt(id);
	dia->show(staff);
	if (dia->exec() == QDialog::Rejected)
	{
		return;
	}
	mInfo = staff;
	accept();
}

void ChoseStaffDialog::setAccessData(const QByteArray &value)
{
	access_data = value;
}

void ChoseStaffDialog::show()
{
	auto& cfg = Singlenton<Config>::getInstance();
	uiw->show(cfg.getUrlStaffShortInfo(), cfg.getTimeout(), access_data);
}

ShortStaffInfo ChoseStaffDialog::getStaffIinfo() const
{
	return mInfo;
}

