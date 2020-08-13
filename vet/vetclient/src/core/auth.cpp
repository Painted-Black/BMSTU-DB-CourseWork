#include "auth.h"
#include "ui_auth_dialog.h"

Auth::Auth(QWidget *parent)
    : QDialog(parent), ui(new Ui::auth_dialog())
{
    ui->setupUi(this);
}
