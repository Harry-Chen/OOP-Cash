#include "calendardialog.h"
#include "ui_calendardialog.h"

CalendarDialog::CalendarDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CalendarDialog)
{
	ui->setupUi(this);
	connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SIGNAL(seletedDateChanged()));
}

QDate CalendarDialog::getSelectedDate()
{
	return ui->calendarWidget->selectedDate();
}

CalendarDialog::~CalendarDialog()
{
	delete ui;
}

void CalendarDialog::on_conformBtn_clicked()
{
	this->setVisible(false);
}
