#include "prescribings_table_model.h"

void PrescribingsTableModel::setTableData(const QList<QStringList> &d)
{
    m_data = d;
}

int PrescribingsTableModel::rowCount(const QModelIndex &) const
{
    return m_data.size();
}

int PrescribingsTableModel::columnCount(const QModelIndex &) const
{
    return m_data.first().size();
}

QVariant PrescribingsTableModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int column = index.column();

    /*View*/
    if (role == Qt::DisplayRole)
    {
        return m_data[row][column];
    }

    return QVariant();
}
