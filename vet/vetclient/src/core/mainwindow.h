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
	explicit MainWindow(AccessLevel level, QWidget *parent = nullptr);
	void setAccessData(const AccessData &value);
	void show();

private:
	void constructAdmin();
	void constructVet();
	void constructReistry();
	void constructMain();

	void runAnimalEditor();
	void showMainTab(QWidget* w);
	void showAdminPannel(QWidget* w);
	QWidget *addTab(const QIcon&, const QString&, std::tuple<uint64_t,  uint8_t> , InitFunc<QWidget*>);
	std::tuple<bool, QWidget*> findTag(uint64_t) const;
	void addToolBarAction(const QIcon&, const QString&, const Callback& cb);
	void closeTab(int);
	void createWidgetAnimals(QWidget*);
	void createWidgetAnimalInfo(uint64_t);
	void createWidgetNewAnimal();
	void updateAnimal();
	void createWidgetAccountInfo(QWidget*);
	void createWidgetNewVisit(QWidget*);
	void accInfo();
	void exit();
public slots:
	void newVisit();
	void patients();
private:
	Ui::MainWindow* ui;
	Staff staff;
	AccessData access_data;
};
