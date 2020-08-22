#include "prescribings_widget.h"
#include "ui_prescribings_widget.h"

prescribings_widget::prescribings_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::prescribings_widget)
{
    ui->setupUi(this);
}

prescribings_widget::~prescribings_widget()
{
    delete ui;
}
