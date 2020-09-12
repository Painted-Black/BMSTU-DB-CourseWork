#pragma once

#include <QAbstractTableModel>
#include <QVariant>

#include "types/shedules_short_info.h"

class SchedulesTableModel : public QAbstractTableModel
{
public:
	enum Column
	{
		FIO				= 0,
		POSITION		= 1,
		SUN				= 2,
		MON				= 3,
		TUE				= 4,
		WED				= 5,
		THU				= 6,
		FRI				= 7,
		SAT				= 8
	};

	void setTableData(QVector<ShedulesShortInfo> &data);
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	const ShedulesShortInfo& dataAt(int row);
	void setDataAt(int row, const ShedulesShortInfo& new_data);
	void addData(const ShedulesShortInfo& info);
private:
	QVector<ShedulesShortInfo> mData;
	int mColumnCount = 9;
};

