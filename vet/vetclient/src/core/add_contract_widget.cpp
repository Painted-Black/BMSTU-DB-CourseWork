#include "ui_add_contract.h"
#include "add_contract_widget.h"

AddContractWidget::AddContractWidget(QWidget * parent)
	: QWidget(parent), ui(new Ui::add_constract_widget())
{
	ui->setupUi(this);
}
