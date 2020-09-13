#include <QAction>
#include <QDebug>
#include "contacts.h"
#include "ui_contacts.h"

Q_DECLARE_METATYPE(QLineEdit*)

Contacts::Contacts(QWidget * parent)
	: QWidget(parent), ui(new Ui::contacts_widget())
{
	ui->setupUi(this);
	ui->template_box->setVisible(false);
	qRegisterMetaType<QLineEdit*>();
	connect(ui->phone_toolButton, &QToolButton::clicked, this, &Contacts::createFieldPhone);
	connect(ui->email_toolButton, &QToolButton::clicked, this, &Contacts::createFieldEmail);
	connect(ui->social_toolButton, &QToolButton::clicked, this, &Contacts::createFieldSocial);
}

void Contacts::addNewPhone(const QString & phone)
{
	QLineEdit* phone_edit = ui->phone_lineEdit;
	QLineEdit* new_phone = new QLineEdit();
	new_phone->setInputMask(phone_edit->inputMask());
	new_phone->setFont(phone_edit->font());
	new_phone->setText(phone);
	auto* lay = static_cast<QGridLayout*>(ui->phones_frame->layout());
	int row = lay->rowCount();

	lay->addWidget(new_phone, row, 1);

	QToolButton* delete_btn = new QToolButton();
	delete_btn->setPalette(ui->template_box->palette());
	delete_btn->setText(ui->template_box->text());
	delete_btn->setMinimumSize(ui->phone_toolButton->size());
	lay->addWidget(delete_btn, row, 2);
	delete_btn->setProperty("p_id", qVariantFromValue(new_phone));

	connect(delete_btn, &QToolButton::clicked, this, &Contacts::deleteItem);
}

void Contacts::addNewEmail(const QString & email)
{
	QLineEdit* email_edit = ui->email_lineEdit;
	QLineEdit* new_email = new QLineEdit();
	new_email->setInputMask(email_edit->inputMask());
	new_email->setFont(email_edit->font());
	new_email->setText(email);
	auto* lay = static_cast<QGridLayout*>(ui->email_frame->layout());
	int row = lay->rowCount();

	lay->addWidget(new_email, row, 1);

	QToolButton* delete_btn = new QToolButton();
	delete_btn->setPalette(ui->template_box->palette());
	delete_btn->setText(ui->template_box->text());
	delete_btn->setMinimumSize(ui->email_toolButton->size());
	lay->addWidget(delete_btn, row, 2);
	delete_btn->setProperty("p_id", qVariantFromValue(new_email));

	connect(delete_btn, &QToolButton::clicked, this, &Contacts::deleteItem);
}

void Contacts::addNewSocialSite(const QUrl & url)
{
	QLineEdit* social_edit = ui->social_lineEdit;
	QLineEdit* new_social = new QLineEdit();
	new_social->setFont(social_edit->font());
	new_social->setText(url.toString());
	auto* lay = static_cast<QGridLayout*>(ui->social_frame->layout());
	int row = lay->rowCount();

	lay->addWidget(new_social, row, 1);

	QToolButton* delete_btn = new QToolButton();
	delete_btn->setPalette(ui->template_box->palette());
	delete_btn->setText(ui->template_box->text());
	delete_btn->setMinimumSize(ui->social_toolButton->size());
	lay->addWidget(delete_btn, row, 2);
	delete_btn->setProperty("p_id", qVariantFromValue(new_social));

	connect(delete_btn, &QToolButton::clicked, this, &Contacts::deleteItem);
}

QStringList Contacts::getPhones() const
{
	QStringList out;
	auto edits = ui->phones_frame->findChildren<QLineEdit*>();
	for (const auto& edit : edits)
	{
		QString text = edit->text();
		if (text.isEmpty() == false)
		{
			out.push_back(text);
		}
	}

	return out;
}

QStringList Contacts::getEmails() const
{
	QStringList out;
	auto edits = ui->email_frame->findChildren<QLineEdit*>();
	for (const auto& edit : edits)
	{
		QString text = edit->text();
		if (text.isEmpty() == false)
		{
			out.push_back(text);
		}
	}

	return out;
}

QList<QUrl> Contacts::getSocialSites() const
{
	decltype (getSocialSites()) out;
	auto edits = ui->social_frame->findChildren<QLineEdit*>();
	for (const auto& edit : edits)
	{
		QUrl text = edit->text();
		if (text.isEmpty() == false && text.isValid())
		{
			out.push_back(text);
		}
	}

	return out;
}

void Contacts::deleteItem()
{
	QToolButton* button = static_cast<QToolButton*>(sender());
	QLineEdit* edit = qvariant_cast<QLineEdit*>(button->property("p_id"));
	auto* lay = static_cast<QGridLayout*>(ui->phones_frame->layout());
	lay->removeWidget(button);
	lay->removeWidget(edit);
	button->deleteLater();
	edit->deleteLater();
	qDebug() << lay->rowCount();
}

void Contacts::createFieldPhone()
{
	addNewPhone(QString());
}

void Contacts::createFieldEmail()
{
	addNewEmail(QString());
}

void Contacts::createFieldSocial()
{
	addNewSocialSite(QUrl());
}
