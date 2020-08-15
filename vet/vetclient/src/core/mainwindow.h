#pragma once

#include <QMainWindow>

#include "account_info_widget.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);

private:
	void runAnimalEditor();
	void addTab(const QIcon&, const QString&, std::tuple<uint64_t,  uint8_t> flags);
	void closeTab(int);

private:
	Ui::MainWindow* ui;

private slots:
	void accInfo();
	void exit();
};

