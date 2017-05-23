#include "dateeditcalendar.h"
#include "ui_dateeditcalendar.h"
#include "ui/calendardialog.h"

DateEditCalendar::DateEditCalendar(QWidget *parent):
    QDateEdit(parent),
    ui(new Ui::DateEditCalendar)
{
    ui->setupUi(this);
    calendar = new CalendarDialog;
    connect(calendar, SIGNAL(seletedDateChanged()), this, SLOT(setDateByCalendar()));
    ui->lineEdit->setText(QDate().currentDate().toString("yyyy-MM-dd"));
    //ui->lineEdit->setVisible(false);
}

void DateEditCalendar::setDateByCalendar()
{
    QDate date = calendar->getSelectedDate();
    ui->lineEdit->setText(date.toString("yyyy-MM-dd"));
    setDate(date);
}

DateEditCalendar::~DateEditCalendar()
{
    delete ui;
}

void DateEditCalendar::on_btnCalendar_clicked()
{
    calendar->setVisible(true);
}
