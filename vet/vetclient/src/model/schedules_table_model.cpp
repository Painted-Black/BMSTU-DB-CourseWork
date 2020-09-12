#include "schedules_table_model.h"

#include <QColor>


void SchedulesTableModel::setTableData(QVector<ShedulesShortInfo> &data)
{
	beginResetModel();
	mData = data;
	endResetModel();
}

int SchedulesTableModel::rowCount(const QModelIndex &) const
{
	return mData.size();
}

int SchedulesTableModel::columnCount(const QModelIndex &) const
{
	return mColumnCount;
}

QVariant SchedulesTableModel::data(const QModelIndex &index, int role) const
{
	int row = index.row();
	int column = index.column();
	ShedulesShortInfo info = mData.at(row);
	ScheduleList cur_list = info.schedList();

	/*View*/
	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
			case FIO:				return info.fio();
			case POSITION:			return info.posTitle();
			case SUN:				return cur_list.getScheduleByDay(DayOfWeek::DayOfWeekEnum::Sun);
			case MON:				return cur_list.getScheduleByDay(DayOfWeek::DayOfWeekEnum::Mon);
			case TUE:				return cur_list.getScheduleByDay(DayOfWeek::DayOfWeekEnum::Tue);
			case WED:				return cur_list.getScheduleByDay(DayOfWeek::DayOfWeekEnum::Wed);
			case THU:				return cur_list.getScheduleByDay(DayOfWeek::DayOfWeekEnum::Thu);
			case FRI:				return cur_list.getScheduleByDay(DayOfWeek::DayOfWeekEnum::Fri);
			case SAT:				return cur_list.getScheduleByDay(DayOfWeek::DayOfWeekEnum::Sat);
			default: return QVariant();
		}
	}
	return QVariant();
}

QVariant SchedulesTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
		case FIO:				return QString(" Фамилия И.О. ");
		case POSITION:			return QString(" Должность ");
		case SUN:				return QString(" Воскресенье ");
		case MON:				return QString(" Понедельник ");
		case TUE:				return QString(" Вторник ");
		case WED:				return QString(" Среда ");
		case THU:				return QString(" Четверг ");
		case FRI:				return QString(" Пятница ");
		case SAT:				return QString(" Суббота ");
		default: return QVariant();
	}
	return QVariant();
}

const ShedulesShortInfo &SchedulesTableModel::dataAt(int row)
{
	return mData.at(row);
}

void SchedulesTableModel::setDataAt(int row, const ShedulesShortInfo &new_data)
{
	beginResetModel();
	mData[row] = new_data;
	endResetModel();
}

void SchedulesTableModel::addData(const ShedulesShortInfo &info)
{
	int data_size = mData.size();
	beginInsertRows(QModelIndex(), data_size, data_size);
	mData.append(info);
	endInsertRows();
}
