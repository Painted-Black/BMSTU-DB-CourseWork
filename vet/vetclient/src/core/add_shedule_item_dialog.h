#pragma once

#include <QDialog>
#include "types/schedule.h"

namespace Ui {
class AddSheduleItemDialog;
}

class AddSheduleItemDialog : public QDialog
{
	Q_OBJECT

public:
	explicit AddSheduleItemDialog(QWidget *parent = nullptr);
	~AddSheduleItemDialog();

	Schedule newShedule() const;

private:
	void accept() override;
	void hideErrorLabels();

	Ui::AddSheduleItemDialog *ui;
	Schedule mNewShedule;
};

