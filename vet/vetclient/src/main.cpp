#include <QApplication>
#include "core/mainwindow.h"
#include "core/auth.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Auth a_d;
    if (a_d.exec() == QDialog::Rejected)
    {
        return 0;
    }
    return a.exec();
}
