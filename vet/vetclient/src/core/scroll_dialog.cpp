#include "scroll_dialog.h"
#include "ui_scroll_dialog.h"

ScrollDialog::ScrollDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ScrollDialog)
{
	ui->setupUi(this);
}

ScrollDialog::~ScrollDialog()
{
	delete ui;
}

void ScrollDialog::setWidget(QWidget *w)
{
	ui->scrollArea->setWidget(w);
}
