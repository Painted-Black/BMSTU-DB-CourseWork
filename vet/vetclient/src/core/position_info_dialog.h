#pragma once

#include <QDialog>

#include "types/position.h"

namespace Ui {
class PositionInfoDialog;
}

class PositionInfoDialog : public QDialog
{
	Q_OBJECT

public:
	explicit PositionInfoDialog(QWidget *parent = nullptr);
	~PositionInfoDialog();
	void show(const Position& pos);
	bool isChanged() const;
	Position getNewPosition();
	void setPassword(const QByteArray &value);

private:
	void save();
	bool queryToServer();

	Ui::PositionInfoDialog *ui;
	Position old_position;
	Position new_position;
	QByteArray password;
	bool mIsChanged;
};

