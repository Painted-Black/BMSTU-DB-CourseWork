#pragma once

#include <QItemDelegate>

class AnimalListDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	AnimalListDelegate(QObject*);
	QWidget *createEditor(QWidget *, const QStyleOptionViewItem &,const QModelIndex &) const override;
	void setModelData(QWidget *, QAbstractItemModel *, const QModelIndex &) const override;
	void updateEditorGeometry(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const override;
	void setEditorData(QWidget *editor, const QModelIndex &index) const override;
};

