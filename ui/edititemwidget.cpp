#include "edititemwidget.h"
#include "ui_edititemwidget.h"

editItemWidget::editItemWidget(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::editItemWidget)
{
	ui->setupUi(this);
}

editItemWidget::~editItemWidget()
{
	delete ui;
}
