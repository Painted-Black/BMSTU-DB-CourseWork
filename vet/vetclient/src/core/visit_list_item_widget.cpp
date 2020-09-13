#include "visit_list_item_widget.h"
#include "ui_visit_list_item_widget.h"

VisitListItemWidget::VisitListItemWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::VisitListItemWidget)
{
	ui->setupUi(this);

	mView = new QListWidget(this);
	QHBoxLayout* lay = new QHBoxLayout(this);
	lay->addWidget(mView);
	setLayout(lay);
}

VisitListItemWidget::~VisitListItemWidget()
{
	delete ui;
}

void VisitListItemWidget::addVisit(const ShortVisitInfo &visit)
{
	mData.append(visit);
	addWidget(visit);
}

void VisitListItemWidget::addVisitsVec(const QVector<ShortVisitInfo> &vec)
{
	int size = vec.size();
	for (int i = 0; i < size; ++i)
	{
		addVisit(vec.at(i));
	}
}

void VisitListItemWidget::addWidget(const ShortVisitInfo &visit)
{
	QListWidgetItem* item = new QListWidgetItem(mView);

	QWidget* inserted_widget = new QWidget();
	Ui::VisitListItemWidget* ui = new Ui::VisitListItemWidget();
	ui->setupUi(inserted_widget);
	ui->input_date_label->setText(visit.visitDate().toString());
	ui->input_spec_label->setText(visit.animalSpecies());
	ui->inpur_animal_label->setText(visit.animalName());
	ui->input_doctor_label->setText(visit.docFio());

	mView->addItem(item);
	item->setSizeHint(inserted_widget->sizeHint());
	mView->setItemWidget(item, inserted_widget);
}
