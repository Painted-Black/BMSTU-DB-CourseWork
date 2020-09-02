#pragma once

#include <QDialog>

#include "types/user_data.h"

namespace Ui {
class ChoseAccessLevelDialog;
}

class ChoseAccessLevelDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ChoseAccessLevelDialog(QWidget *parent = nullptr);
	~ChoseAccessLevelDialog();
	void setOldAccesslevel(const QString &level);
	QString getAccessLevel() const;
	void accept() override;
private:
	Ui::ChoseAccessLevelDialog *ui;
	QString access_level;
};

