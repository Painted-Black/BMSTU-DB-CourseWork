#pragma once

#include <functional>
#include <QMainWindow>
#include <QByteArray>
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
	template<typename T>
	using InitFunc = void(MainWindow::*)(T);
public:
	explicit MainWindow(QWidget *parent = nullptr);

	void setAccessData(const AccessData &value);

private:
	void runAnimalEditor();
	QWidget *addTab(const QIcon&, const QString&, std::tuple<uint64_t,  uint8_t> , InitFunc<QWidget*>);
	void addToolBarAction(const QIcon&, const QString&, const Callback& cb);
	void closeTab(int);
	void createWidgetAnimals(QWidget*);
	void createWidgetAccountInfo(QWidget*);

private:
	Ui::MainWindow* ui;
	Staff staff;
	AccessData access_data;
private slots:
	void accInfo();
	void exit();
};

