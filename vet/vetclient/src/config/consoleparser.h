#pragma once

#include <memory>
#include <QStringList>

class ConsoleParser final
{
	struct Data;
public:
	ConsoleParser();
	~ConsoleParser() noexcept;
	void parse(const QStringList&);
	const QString& getPathToConfig() const;

private:
	std::unique_ptr<Data> data;
};

