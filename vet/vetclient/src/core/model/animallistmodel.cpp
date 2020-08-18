#include "animallistmodel.h"

int AnimalListModel::rowCount(const QModelIndex &) const
{
	return animal_info.size();
}

int AnimalListModel::columnCount(const QModelIndex &) const
{
	return 1;
}

QVariant AnimalListModel::data(const QModelIndex &index, int role) const
{
	if (role == Qt::DisplayRole)
	{
		return animal_info[index.row()].getName();
	}
	else if (role == Qt::EditRole)
	{
		return animal_info[index.row()].getName();
	}

	return QVariant();
}

void AnimalListModel::dataChanged(const QModelIndex & up, const QModelIndex& down, const QVector<int> & roles)
{
	int i = 0;
	i++;
}

void AnimalListModel::setAnimalsInfo(const QVector<ShortAnimalInfo> & a)
{
	animal_info = a;
}

void AnimalListModel::setAnimalsInfo(QVector<ShortAnimalInfo> && d)
{
	animal_info = d;
}
