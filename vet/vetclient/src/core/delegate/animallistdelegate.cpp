#include <QDebug>
#include "animallistdelegate.h"
#include "ui_animal_list_item_widget.h"

AnimalListDelegate::AnimalListDelegate(QObject * w)
	: QItemDelegate(w)
{
}

QWidget *AnimalListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
	QWidget* new_widget = new QWidget(parent);
	Ui::Form* form = new Ui::Form();
	form->setupUi(new_widget);
	return new_widget;
}

void AnimalListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	model->setData(index, "Some text", Qt::EditRole);
	qDebug() << Q_FUNC_INFO;
}

void AnimalListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	qDebug() <<Q_FUNC_INFO;
}

void AnimalListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	qDebug() <<Q_FUNC_INFO;
}
