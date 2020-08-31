#include "prescribings_table_model.h"

void PrescribingsTableModel::setTableData(const Prescribings& p)
{
	m_data = p;
	keys = m_data.keys();
}

int PrescribingsTableModel::rowCount(const QModelIndex &) const
{
	return m_data.size();
}

int PrescribingsTableModel::columnCount(const QModelIndex &) const
{
	return 6;
}

QVariant PrescribingsTableModel::data(const QModelIndex &index, int role) const
{
	int row = index.row();
	int column = index.column();
	const QString& key = keys.at(row);
	Medicine med = m_data.at(key);

	/*View*/
	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
			case NAME: return med.getName();
			case DOSAGE: return med.getDosage();
			case TYPE: return med.getType().toString();
			case FREQUENCY: return med.getFrequency_of_medication();
			case TERM: return med.getTerm_of_taking();
			case NOTE: return med.getNotes();
			default: return QVariant();
		}
	}
	return QVariant();
}

void PrescribingsTableModel::addMed(const Medicine &med)
{
	int data_size = m_data.size();
	beginInsertRows(QModelIndex(), data_size, data_size);
	m_data.append(med);
	endInsertRows();
	keys = m_data.keys();
}

void PrescribingsTableModel::removeMed(const QString &name, int index)
{
	beginRemoveRows(QModelIndex(), index, index);
	m_data.remove(name);
	endRemoveRows();
	keys = m_data.keys();
}

QVariant PrescribingsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
		case NAME:
			return QString(" Название ");
		case DOSAGE:
			return QString(" Дозировка ");
		case TYPE:
			return QString(" Тип ");
		case FREQUENCY:
			return QString(" Частота приема ");
		case TERM:
			return QString(" Длительность приема ");
		case NOTE:
			return QString(" Примечание ");
	}
	return QVariant();
}

Prescribings &PrescribingsTableModel::getPresctibings()
{
	return m_data;
}
