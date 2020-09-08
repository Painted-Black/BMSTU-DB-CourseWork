#include "staff_schedule_tablemodel.h"
#include "QHeaderView"

void StaffScheduleTableModel::setTableData(QVector<Schedule> &data)
{
	beginResetModel();
	mData = data;
	endResetModel();
}

int StaffScheduleTableModel::rowCount(const QModelIndex &) const
{
	return mData.size();
}

int StaffScheduleTableModel::columnCount(const QModelIndex &) const
{
	return mColumnCount;
}

QVariant StaffScheduleTableModel::data(const QModelIndex &index, int role) const
{
	int row = index.row();
	int column = index.column();
	const Schedule& info = mData.at(row);

	/*View*/
	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
			case DAY:			return info.getDay_of_week().toString();
			case START:			return info.getStart().toString();
			case END:			return info.getEnd().toString();
			case CABINET:		return info.getCabinet();
			default: return QVariant();
		}
	}
	return QVariant();
}

QVariant StaffScheduleTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
	{
		return QVariant();
	}
	if (orientation == Qt::Vertical)
	{
		return section;
	}
	switch (section)
	{
		case DAY:			return QString(" День ");
		case START:			return QString(" Начало ");
		case END:			return QString(" Конец ");
		case CABINET:		return QString(" Кабинет ");
	default: return QVariant();
	}
	return QVariant();
}

const Schedule &StaffScheduleTableModel::dataAt(int row)
{
	return mData.at(row);
}

void StaffScheduleTableModel::setDataAt(int row, const Schedule &new_data)
{
	beginResetModel();
	mData[row] = new_data;
	endResetModel();
}

void StaffScheduleTableModel::addData(const Schedule &info)
{
	int data_size = mData.size();
	beginInsertRows(QModelIndex(), data_size, data_size);
	mData.append(info);
	endInsertRows();
}

void StaffScheduleTableModel::removeAt(int row)
{
	beginRemoveRows(QModelIndex(), row, row);
	mData.remove(row);
	endRemoveRows();
}

QVector<Schedule> StaffScheduleTableModel::getAllData()
{
	return mData;
}
