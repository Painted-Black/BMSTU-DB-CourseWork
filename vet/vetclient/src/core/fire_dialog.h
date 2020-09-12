#pragma once

#include <QDialog>
#include <QDate>

namespace Ui {
class FireDialog;
}

class FireDialog : public QDialog
{
	Q_OBJECT

public:
	explicit FireDialog(QWidget *parent = nullptr);
	~FireDialog();
	void accept() override;

	QDate getFireDate() const;

private:
	Ui::FireDialog *ui;
	QDate mFireDate;
};

