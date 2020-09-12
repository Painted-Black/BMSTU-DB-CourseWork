#include "staff_table_model.h"

void StaffTableModel::setTableData(QVector<Staff> &data)
{
	mAllData = data;
	mOnlyEmployedData.clear();
	for (int i = 0; i < mAllData.size(); ++i)
	{
		if (mAllData.at(i).getFire_date().isValid() == false)
		{
			mOnlyEmployedData.push_back(mAllData.at(i));
		}
	}
	beginResetModel();
	if (mShowAll == true)
	{
		mData = &mAllData;
	}
	else
	{
		mData = &mOnlyEmployedData;
	}
	endResetModel();
//	mData = data;
}

int StaffTableModel::rowCount(const QModelIndex &) const
{
	return mData->size();
}

int StaffTableModel::columnCount(const QModelIndex &) const
{
	return mColumnCount;
}

QVariant StaffTableModel::data(const QModelIndex &index, int role) const
{
	int row = index.row();
	int column = index.column();
	Staff info = mData->at(row);
	const Passport& pass = info.getPassport();
	const Position& pos = info.getPosition();

	/*View*/
	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
			case FIO:			return QVariant::fromValue(pass.getFio());
			case POSITION:		return pos.getTitle();
			case EMPL_DATE:		return info.getEmploy_date().toString();
			case FIRE_DATE:		return info.getFire_date().toString();
			default: return QVariant();
		}
	}
	return QVariant();
}

QVariant StaffTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
	case FIO:			return QString(" Фамилия И.О. ");
	case POSITION:		return QString(" Должность ");
	case EMPL_DATE:		return QString(" Принят ");
	case FIRE_DATE:		return QString(" Уволен ");
	}
	return QVariant();
}

const Staff &StaffTableModel::dataAt(int row)
{
	return mData->at(row);
}

void StaffTableModel::setDataAt(int row, const Staff &new_data)
{
	beginResetModel();
	if (mShowAll == true)
	{
		mAllData[row] = new_data;
		for (int i = 0; i < mOnlyEmployedData.size(); ++i)
		{
			if (mOnlyEmployedData[i].getId() == new_data.getId())
			{
				mOnlyEmployedData.remove(i);
				break;
			}
		}
	}
	else
	{
		mOnlyEmployedData[row]=new_data;
		for (int i = 0; i < mAllData.size(); ++i)
		{
			if (mOnlyEmployedData[i].getId() == new_data.getId())
			{
				mOnlyEmployedData.remove(i);
				break;
			}
		}

	}
	endResetModel();
}

void StaffTableModel::addData(const Staff &info)
{
	int data_size = mData->size();
	beginInsertRows(QModelIndex(), data_size, data_size);
	mData->append(info);
	endInsertRows();
}

void StaffTableModel::showAll()
{
	mShowAll = true;
	beginResetModel();
	mData = &mAllData;
	endResetModel();
}

void StaffTableModel::showOnlyEmployed()
{
	mShowAll = false;
	beginResetModel();
	mData = &mOnlyEmployedData;
	endResetModel();
}
