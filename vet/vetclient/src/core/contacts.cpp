#include "contacts.h"
#include "ui_contacts.h"

Contacts::Contacts(QWidget * parent)
	: QWidget(parent), ui(new Ui::contacts_widget())
{
	ui->setupUi(this);
	connect(ui->phone_toolButton, &QToolButton::clicked, this, &Contacts::createFieldPhone);
}

void Contacts::addNewPhone(const QString & phone)
{
	QLineEdit* phone_edit = ui->phone_lineEdit;
	auto* lay = static_cast<QGridLayout*>(ui->phones_frame->layout());
	lay->addWidget(new QLineEdit(phone, phone_edit->parentWidget()), lay->rowCount(), 1);
}

void Contacts::createFieldPhone()
{
	addNewPhone(QString());
}
