#pragma once

#include <QAbstractTableModel>
#include <QVector>
#include "types/short_animal_info.h"

class AnimalListModel : public QAbstractListModel
{
public:
	virtual int rowCount(const QModelIndex & = QModelIndex()) const override;
	virtual int columnCount(const QModelIndex & = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex &, int = Qt::DisplayRole) const override;
	virtual void dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> & = QVector<int>());
	void setAnimalsInfo(const QVector<ShortAnimalInfo> &);
	void setAnimalsInfo(QVector<ShortAnimalInfo>&&);

private:
	QVector<ShortAnimalInfo> animal_info;
};

