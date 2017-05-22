#include "usersetdialog.h"
#include "ui_usersetdialog.h"

userSetDialog::userSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userSetDialog)
{
    ui->setupUi(this);
}

userSetDialog::~userSetDialog()
{
    delete ui;
}
