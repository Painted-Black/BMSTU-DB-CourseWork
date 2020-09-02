#include "question_dialog.h"
#include "ui_question_dialog.h"

QuestionDialog::QuestionDialog(QString question, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::QuestionDialog)
{
	ui->setupUi(this);
	ui->question_label->setText(question);
}

QuestionDialog::~QuestionDialog()
{
	delete ui;
}
