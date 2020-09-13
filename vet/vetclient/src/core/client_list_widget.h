#pragma once

#include <QDialog>
#include <QListWidget>
#include "types/contract.h"

namespace Ui
{
	class ClientWidgetList;
}

Q_DECLARE_METATYPE(ShortInfoClient)

class ClientListWidget : public QWidget
{
	Q_OBJECT
public:
	explicit ClientListWidget(QWidget *parent = nullptr);
	std::tuple<bool, QString> requestData(const QUrl &, std::chrono::milliseconds, const QByteArray &);
	void setData(QVector<ShortInfoClient>&&);
	void update();
	const ShortInfoClient& getSelectedClient() const;

private:
	QWidget* addWidget(const ShortInfoClient & info);

Q_SIGNALS:
	void selectClient(int);
	void inrerrupt();

private:
	Ui::ClientWidgetList* ui;
	QVector<ShortInfoClient> clients;
	int selected_row_buffer;
};

