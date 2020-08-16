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

	auto auth_data = a_d.getAuthData();

	MainWindow mw;
	mw.setAccessData(std::get<0>(auth_data));
	mw.setKey(std::get<1>(auth_data));
	mw.show();

	return a.exec();
}
