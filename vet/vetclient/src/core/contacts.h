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
public:
	Contacts(QWidget * = nullptr);

	void addNewPhone(const QString&);

private:
	void createFieldPhone();

private:
	Ui::contacts_widget* ui;
	QStringList phones;
	QStringList emails;
	QList<QUrl> social;
};

