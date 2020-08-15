#include "ui_acc_info.h"
#include "account_info_widget.h"

AccountInfoWidget::AccountInfoWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::acc_info_widget())
{
    ui->setupUi(this);
}
