#pragma once

#include <QAbstractTableModel>
#include <QVariant>

#include "types/position.h"

class PositionsTableModel : public QAbstractTableModel
{
public:
	enum Column
	{
		TITLE				= 0,
		SALARY				= 1,
	};

	void setTableData(QVector<Position> &data);
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	const Position& dataAt(int row);
	void setDataAt(int row, const Position& new_data);
	void addData(const Position& info);
private:
	QVector<Position> mData;
	int mColumnCount = 2;
};

