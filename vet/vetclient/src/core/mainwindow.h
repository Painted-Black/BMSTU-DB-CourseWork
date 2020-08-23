#pragma once

#include <functional>
#include <QNetworkAccessManager>
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
	template<typename T>
	using InitFunc = void(MainWindow::*)(T);
	using  Callback = void(MainWindow::*)();
public:
	explicit MainWindow(QWidget *parent = nullptr);

	void setAccessData(const AccessData &value);

private:
	void runAnimalEditor();
	QWidget *addTab(const QIcon&, const QString&, std::tuple<uint64_t,  uint8_t> , InitFunc<QWidget*>);
	void addToolBarAction(const QIcon&, const QString&, const Callback& cb);
	void closeTab(int);
	void createWidgetAnimals(QWidget*);
	void createWidgetAnimalInfo(uint64_t);
	void createWidgetAccountInfo(QWidget*);

	void createNewAnimal();

	void accInfo();
	void exit();

private:
	Ui::MainWindow* ui;
	Staff staff;
	AccessData access_data;
};

