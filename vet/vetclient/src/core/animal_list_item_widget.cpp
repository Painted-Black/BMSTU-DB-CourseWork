#include "ui_animal_list_item_widget.h"
#include "animal_list_item_widget.h"

AnimalListItemWidget::AnimalListItemWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Form())
{
    ui->setupUi(this);
}
