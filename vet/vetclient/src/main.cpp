#include <QApplication>
#include "core/mainwindow.h"
#include "core/auth.h"

#include "core/network/network_fetcher.h"

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
	mw.setAccessData(auth_data);
	mw.show();

	return a.exec();
}
