#include <QApplication>
#include "core/mainwindow.h"
#include "core/auth.h"
#include "utils/singlenton.h"
#include "core/popup.h"
#include "config/config.h"
#include "config/consoleparser.h"
#include "types/image_loader.h"

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

	auto& config = Singlenton<Config>::Init();
	Q_ASSERT(config.loadConfig(path_to_config));

	bool exit = false;
	while (exit == false)
	{
		Auth a_d;
		if (a_d.exec() == QDialog::Rejected)
		{
			exit = true;
		}
		else
		{
			auto auth_data = a_d.getAuthData();
			auto& notifier = Singlenton<PopUp>::Init();
			ImageLoader::init(config.getUrlPhotoData(), config.getTimeout(), "images", QDir::current());

			notifier.setPopupText(QString("Вы успешно вошли как пользователь %1")
								  .arg(auth_data.getOwner().getPassport().getName()));
			notifier.show();

			MainWindow mw(auth_data);
			mw.show();

			a.exec();
		}
	}

	return 0;
}
