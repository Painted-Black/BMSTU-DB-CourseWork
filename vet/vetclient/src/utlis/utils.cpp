#include <QJsonDocument>
#include "utils.h"

QByteArray toJson(const QJsonObject & obj)
{
	return QJsonDocument(obj).toJson();
}
