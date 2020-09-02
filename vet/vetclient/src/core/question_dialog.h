#pragma once

#include <QDialog>

namespace Ui {
class QuestionDialog;
}

class QuestionDialog : public QDialog
{
	Q_OBJECT

public:
	explicit QuestionDialog(QString question, QWidget *parent = nullptr);
	~QuestionDialog();

private:
	Ui::QuestionDialog *ui;
};

