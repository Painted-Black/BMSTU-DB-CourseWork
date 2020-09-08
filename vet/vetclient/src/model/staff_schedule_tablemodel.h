#pragma once

#include <QAbstractTableModel>

#include "types/schedule.h"

class StaffScheduleTableModel : public QAbstractTableModel
{
public:
	enum Column
	{
		DAY				= 0,
		START			= 1,
		END				= 2,
		CABINET			= 3,
	};

	void setTableData(QVector<Schedule> &data);
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	const Schedule& dataAt(int row);
	void setDataAt(int row, const Schedule& new_data);
	void addData(const Schedule& info);
	void removeAt(int row);
	QVector<Schedule> getAllData();
private:
	QVector<Schedule> mData;
	int mColumnCount = 4;
};
