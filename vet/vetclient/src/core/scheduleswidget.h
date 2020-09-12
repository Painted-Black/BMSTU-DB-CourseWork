#pragma once

#include <QWidget>

#include "model/schedules_table_model.h"

namespace Ui {
class SchedulesWidget;
}

class SchedulesWidget : public QWidget
{
	Q_OBJECT

public:
	explicit SchedulesWidget(QWidget *parent = nullptr);
	~SchedulesWidget();
	void init();

	void setPassword(const QByteArray &password);

private:
	Ui::SchedulesWidget *ui;
	SchedulesTableModel* model;
	QByteArray mPassword;
};

