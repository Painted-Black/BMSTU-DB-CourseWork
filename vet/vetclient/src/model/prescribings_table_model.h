#pragma once

#include <QAbstractTableModel>
#include <QVariant>

#include "types/prescribings.h"

class PrescribingsTableModel : public QAbstractTableModel
{
public:
    void setTableData(const Prescribings& p);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addMed(const Medicine& med);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    enum Column
    {
        NAME = 0,
        DOSAGE,
        TYPE,
        FREQUENCY,
        TERM,
        NOTE
    };

    Prescribings m_data;
    QStringList keys;
};

