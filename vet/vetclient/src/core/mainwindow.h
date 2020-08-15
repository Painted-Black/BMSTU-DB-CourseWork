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

private:
    Ui::MainWindow* ui;
    QAction *acc_info_action;
    QDockWidget* acc_info_widget;

private slots:
    void accInfo();
    void exit();
};

