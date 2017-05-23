#ifndef DATEEDITCALENDAR_H
#define DATEEDITCALENDAR_H

//#include <QWidget>
#include <QDateEdit>
#include "ui/calendardialog.h"

namespace Ui {
class DateEditCalendar;
}

class DateEditCalendar : public QDateEdit
{
    Q_OBJECT

public:
    explicit DateEditCalendar(QWidget *parent = 0);
    ~DateEditCalendar();

private:
    Ui::DateEditCalendar *ui;
    CalendarDialog * calendar;
    void setDateByCalendar();
private slots:
    void on_btnCalendar_clicked();

};

#endif // DATEEDITCALENDAR_H
