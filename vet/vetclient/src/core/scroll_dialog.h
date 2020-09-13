#pragma once

#include <QDialog>

namespace Ui {
class ScrollDialog;
}

class ScrollDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ScrollDialog(QWidget *parent = nullptr);
	~ScrollDialog();
	void setWidget(QWidget* w);

private:
	Ui::ScrollDialog *ui;
};

