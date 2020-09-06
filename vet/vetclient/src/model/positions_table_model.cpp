#include "positions_table_model.h"

void PositionsTableModel::setTableData(QVector<Position> &data)
{
	beginResetModel();
	mData = data;
	endResetModel();
}

int PositionsTableModel::rowCount(const QModelIndex &) const
{
	return mData.size();
}

int PositionsTableModel::columnCount(const QModelIndex &) const
{
	return mColumnCount;
}

QVariant PositionsTableModel::data(const QModelIndex &index, int role) const
{
	int row = index.row();
	int column = index.column();
	Position info = mData.at(row);

	/*View*/
	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
			case TITLE:			return QVariant::fromValue(info.getTitle());
			case SALARY:			return info.getSalary();
			default: return QVariant();
		}
	}
	return QVariant();
}

QVariant PositionsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
		case TITLE:
			return QString(" Название ");
		case SALARY:
			return QString(" Зарплата ");
	}
	return QVariant();
}

const Position &PositionsTableModel::dataAt(int row)
{
	return mData.at(row);
}

void PositionsTableModel::setDataAt(int row, const Position &new_data)
{
	beginResetModel();
	mData[row] = new_data;
	endResetModel();
}

void PositionsTableModel::addData(const Position &info)
{
	int data_size = mData.size();
	beginInsertRows(QModelIndex(), data_size, data_size);
	mData.append(info);
	endInsertRows();
}
