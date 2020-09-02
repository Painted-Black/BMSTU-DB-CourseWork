#include <QApplication>
#include "core/mainwindow.h"
#include "core/auth.h"
#include "utils/singlenton.h"
#include "core/popup.h"
#include "config/config.h"
#include "config/consoleparser.h"

#include "core/network/network_fetcher.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QString path_to_config;
	{
		ConsoleParser parser;
		parser.parse(a.arguments());
		path_to_config = parser.getPathToConfig();
	}

	Q_ASSERT(path_to_config.isEmpty() == false);

	auto& config = Singlenton<Config>::getInstance();
	Q_ASSERT(config.loadConfig(path_to_config));

	auto& notifier = Singlenton<PopUp>::getInstance();

	Auth a_d;
	if (a_d.exec() == QDialog::Rejected)
	{
		return 0;
	}

	auto auth_data = a_d.getAuthData();

	notifier.setPopupText(QString("Вы успешно вошли как пользователь %1")
						  .arg(auth_data.getOwner().getPassport().getName()));
	notifier.show();

	MainWindow mw(auth_data.getLevel());
	mw.setAccessData(auth_data);
	mw.show();

	return a.exec();
}
