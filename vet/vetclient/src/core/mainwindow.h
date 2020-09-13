#pragma once

#include <functional>
#include <QNetworkAccessManager>
#include <QMainWindow>
#include <QByteArray>
#include "auth.h"
#include "core/client_list_widget.h"

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
	explicit MainWindow(const AccessData &value, QWidget *parent = nullptr);
	void setAccessData(const AccessData &value);
	void show();

private:
	void constructAdmin();
	void constructVet();
	void constructRegistry();
	void constructMain();

	void runAnimalEditor();
	void visits();
	void showStaffList(QWidget *w);
	void showPositionsList(QWidget *w);
	void showMainTab(QWidget* w);
	void showAdminPannel(QWidget* w);
	void showVetTab(QWidget*);
	void showAdminTab(QWidget*);
	void showRegistryTab(QWidget*);
	void showStaff();
	void showPositions();
	void showSchedules();
	void showSchedulesList(QWidget *w);
	QWidget *addTab(const QIcon&, const QString&, std::tuple<uint64_t,  uint8_t> , InitFunc<QWidget*>);
	std::tuple<bool, QWidget*> findTag(uint64_t) const;
	void addToolBarAction(const QIcon&, const QString&, const Callback& cb);
	void closeTab(int);
	void createWidgetAnimals(QWidget*);
	void createWidgetVisits(QWidget*);
	void createWidgetAnimalInfo(uint64_t);
	void createWidgetNewAnimal();
	void updateAnimal();
	void createAnimal();
	void createWidgetAccountInfo(QWidget*);
	void createWidgetNewVisit(QWidget*);
	void createWidgetClientEditor(QWidget*);
	void saveClient(QWidget *, bool);
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
