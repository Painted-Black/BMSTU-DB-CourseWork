#include "users_table_model.h"

void UsersTableModel::setTableData(QVector<ShortUserInfo> data)
{
	beginResetModel();
	mData = data;
	endResetModel();
}

int UsersTableModel::rowCount(const QModelIndex &) const
{
	return mData.size();
}

int UsersTableModel::columnCount(const QModelIndex &) const
{
	return mColumnCount;
}

QVariant UsersTableModel::data(const QModelIndex &index, int role) const
{
	int row = index.row();
	int column = index.column();
	ShortUserInfo info = mData.at(row);

	/*View*/
	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
			case ID:			return QVariant::fromValue(info.getUid());
			case LOGIN:			return info.getLogin();
			case FIO:			return info.getFio();
			case ACCESS_LEVEL:	return info.getAccessLevel();
			case POSITION:		return info.getPositionTitle();
			case EMPLOYED:		return info.getEmployDate().toString();
			case FIRED:			return (info.getFireDate().isValid()) ? (info.getFireDate().toString()) : ("");
			default: return QVariant();
		}
	}
	return QVariant();
}

QVariant UsersTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
		case ID:
			return QString(" Id ");
		case LOGIN:
			return QString(" Логин ");
		case FIO:
			return QString(" Фамилия И.О. ");
		case ACCESS_LEVEL:
			return QString(" Уровень доступа ");
		case POSITION:
			return QString(" Должность ");
		case EMPLOYED:
			return QString(" Принят ");
		case FIRED:
			return QString(" Уволен ");
	}
	return QVariant();
}

ShortUserInfo UsersTableModel::dataAt(int row)
{
	return mData.at(row);
}

void UsersTableModel::removeAt(int row)
{
	beginRemoveRows(QModelIndex(), row, row);
	mData.remove(row);
	endRemoveRows();
}

void UsersTableModel::setDataAt(int row, const ShortUserInfo& new_data)
{
	beginResetModel();
	mData[row] = new_data;
	endResetModel();
}

void UsersTableModel::addData(const ShortUserInfo &info)
{
	int data_size = mData.size();
	beginInsertRows(QModelIndex(), data_size, data_size);
	mData.append(info);
	endInsertRows();
}

