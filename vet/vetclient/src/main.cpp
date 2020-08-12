#include <QApplication>
#include "core/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWnd;
    mainWnd.show();

    return a.exec();
}
