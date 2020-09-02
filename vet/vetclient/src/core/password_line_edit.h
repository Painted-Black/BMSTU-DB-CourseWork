#pragma once

#include <QAction>
#include <QLineEdit>
#include <QToolButton>

class PasswordLineEdit: public QLineEdit
{
public:
	PasswordLineEdit(QWidget *parent=nullptr);
private slots:
	void onPressed();
	void onReleased();
protected:
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
	void focusInEvent(QFocusEvent *event);
	void focusOutEvent(QFocusEvent *event);
private:
	QToolButton *button;
};

