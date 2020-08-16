#pragma once

#include <functional>
#include <QMainWindow>
#include <QByteArray>
#include "account_info_widget.h"
#include "types/staff.h"
#include "types/user_data.h"
#include "auth.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
private:
	using  Callback = void(MainWindow::*)();
public:
	explicit MainWindow(QWidget *parent = nullptr);

    void setAccess_data(const AccessData &value);
	void setKey(const QByteArray &value);

private:
	void runAnimalEditor();
	QWidget *addTab(const QIcon&, const QString&, std::tuple<uint64_t,  uint8_t> flags);
	void addToolBarAction(const QIcon&, const QString&, const Callback& cb);
	void closeTab(int);

private:
	Ui::MainWindow* ui;
	Staff staff;
	AccessData access_data;
	Passport passport;
	QByteArray key;
private slots:
	void accInfo();
	void exit();
};

