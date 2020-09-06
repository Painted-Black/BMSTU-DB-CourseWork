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
	enum DialogType
	{
		EDIT	= 0,
		ADD		= 1
	};

	explicit PositionInfoDialog(DialogType type, QWidget *parent = nullptr);
	~PositionInfoDialog();
	void show(const Position& pos);
	bool isChanged() const;
	Position getNewPosition();
	void setPassword(const QByteArray &value);
	Position getAddedPosition();
private:
	void update();
	void save();
	bool queryToServerUpdate();
	bool queryToServerAdd(Position pos);
	void hideErrorLabels();

	Ui::PositionInfoDialog *ui;
	Position old_position;
	Position new_position;
	Position added_position;
	QByteArray password;
	bool mIsChanged;
	DialogType mType;
};

