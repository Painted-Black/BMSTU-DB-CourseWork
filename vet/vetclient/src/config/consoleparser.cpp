#include <QCommandLineParser>

#include "consoleparser.h"

struct ConsoleParser::Data
{
	QString config_path;
};

ConsoleParser::ConsoleParser() : data(new Data()) {}

ConsoleParser::~ConsoleParser() noexcept = default;

void ConsoleParser::parse(const QStringList & args)
{
	QCommandLineParser parser;

	QCommandLineOption config("c", "main", "Path to configuration file");
	parser.addOption(config);
	parser.process(args);

	data->config_path = parser.value(config);
}

const QString& ConsoleParser::getPathToConfig() const
{
	return data->config_path;
}
