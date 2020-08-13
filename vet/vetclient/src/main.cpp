#include <QApplication>
#include "core/mainwindow.h"
#include "core/auth.h"

int main(int argc, char *argv[])
{

    Auth a_d;
    if (a_d.exec() == QDialog::Rejected)
    {
        return 0;
    }

    QApplication a(argc, argv);
    return a.exec();
}
