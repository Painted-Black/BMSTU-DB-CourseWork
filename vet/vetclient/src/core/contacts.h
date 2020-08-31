#pragma once

#include <QStringList>
#include <QWidget>
#include <QUrl>

namespace Ui
{
	class contacts_widget;
}

class Contacts final : public QWidget
{
	Q_OBJECT
public:
	Contacts(QWidget * = nullptr);

	void addNewPhone(const QString&);
	void addNewEmail(const QString&);
	void addNewSocialSite(const QUrl&);

	QStringList getPhones() const;
	QStringList getEmails() const;
	QList<QUrl> getSocialSites() const;

private:
	void deleteItem();

private:
	void createFieldPhone();
	void createFieldEmail();
	void createFieldSocial();

private:
	Ui::contacts_widget* ui;
	QStringList phones;
	QStringList emails;
	QList<QUrl> social;
};

