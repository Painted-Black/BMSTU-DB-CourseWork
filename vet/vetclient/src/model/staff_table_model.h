#pragma once

#include <QAbstractTableModel>
#include <QVariant>

#include "types/staff.h"

class StaffTableModel : public QAbstractTableModel
{
public:
	enum Column
	{
		FIO			= 0,
		POSITION	= 1,
		EMPL_DATE	= 2,
		FIRE_DATE	= 3
	};

	void setTableData(QVector<Staff> &data);
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	const Staff& dataAt(int row);
	void setDataAt(int row, const Staff& new_data);
	void addData(const Staff& info);
private:
	QVector<Staff> mData;
	int mColumnCount = 4;
};

