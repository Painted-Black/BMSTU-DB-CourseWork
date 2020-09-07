#pragma once

#include <QDialog>
#include <QListWidget>
#include "types/contract.h"

namespace Ui
{
	class ClientListWidget;
}

Q_DECLARE_METATYPE(ShortInfoClient)

class ClientListWidget : public QDialog
{
	Q_OBJECT
public:
	explicit ClientListWidget(QWidget *parent = nullptr);
	void setData(QVector<ShortInfoClient>&&);
	void update();
	const ShortInfoClient& getSelectedClient() const;

private:
	QWidget* addWidget(const ShortInfoClient & info);

private:
	Ui::ClientListWidget* ui;
	QVector<ShortInfoClient> clients;
	int selected_row_buffer;
};

