#include "changebillwidget.h"
#include "ui_changebillwidget.h"

ChangeBillWidget::ChangeBillWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChangeBillWidget)
{
	ui->setupUi(this);
}

ChangeBillWidget::~ChangeBillWidget()
{
	delete ui;
}
