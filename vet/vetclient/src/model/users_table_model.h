#pragma once

#include <QAbstractTableModel>

#include "types/short_user_info.h"

class UsersTableModel : public QAbstractTableModel
{
public:
	enum Column
	{
		ID				= 0,
		LOGIN			= 1,
		FIO				= 2,
		ACCESS_LEVEL	= 3,
		POSITION		= 4,
		EMPLOYED		= 5,
		FIRED			= 6,
	};

	void setTableData(QVector<ShortUserInfo> data);
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	ShortUserInfo dataAt(int row);
	void removeAt(int row);
	void setDataAt(int row, const ShortUserInfo &new_data);
	void addData(const ShortUserInfo& info);
private:
	int mColumnCount = 7;
	QVector<ShortUserInfo> mData;
};

