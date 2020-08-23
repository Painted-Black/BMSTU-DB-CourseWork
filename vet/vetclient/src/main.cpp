#include <QApplication>
#include "core/mainwindow.h"
#include "core/auth.h"
#include "utlis/singlenton.h"
#include "core/popup.h"

#include "core/network/network_fetcher.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PopUp& notifier = Singlenton<PopUp>::getInstance();

	Auth a_d;
	if (a_d.exec() == QDialog::Rejected)
	{
		return 0;
	}

	auto auth_data = a_d.getAuthData();

	notifier.setPopupText(QString("Вы успешно вошли как пользователь %1")
						  .arg(auth_data.getOwner().getPassport().getName()));
	notifier.show();

	MainWindow mw;
	mw.setAccessData(auth_data);
	mw.show();

	return a.exec();
}
