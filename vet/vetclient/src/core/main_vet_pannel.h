#pragma once

#include <QWidget>

#include "model/positions_table_model.h"

namespace Ui {
class MainVetPannel;
}

class MainVetPannel : public QWidget
{
	Q_OBJECT

public:
	explicit MainVetPannel(QWidget *parent = nullptr);
	~MainVetPannel();
	void update();
	void setPassword(const QByteArray& pass);

private:
	void tableViewDoubleClicked(const QModelIndex &index);

	Ui::MainVetPannel *ui;
	PositionsTableModel* model;
	QByteArray password;
};

