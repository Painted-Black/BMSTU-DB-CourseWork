#include "users_table_model.h"

void UsersTableModel::setTableData(QVector<ShortUserInfo> data)
{
	removeRows(0, mData.size());
	int new_data_size = data.size();
	beginInsertRows(QModelIndex(), 0, new_data_size);
	mData = data;
	endInsertRows();
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
