#pragma once

#include <QAbstractTableModel>

class PrescribingsTableModel : public QAbstractTableModel
{
public:
    void setTableData(const QList<QStringList>&d);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QList<QStringList> m_data;
};

