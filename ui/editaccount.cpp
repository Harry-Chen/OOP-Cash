#include "editaccount.h"
#include "ui_editaccount.h"

editAccount::editAccount(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::editAccount)
{
	ui->setupUi(this);
}

editAccount::~editAccount()
{
	delete ui;
}
