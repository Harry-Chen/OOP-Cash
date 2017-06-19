#ifndef QUERYWIDGET_H
#define QUERYWIDGET_H

#include <QWidget>
#include <QString>
#include "dao/query.h"
#include "plot/billsplotsystem.h"
#include "dao/usermanager.h"
#include "dao/currencymanager.h"
#include "dao/accountmanager.h"
#include "dao/categorymanager.h"
#include "dao/billmanager.h"
#include "util/database_helper.h"
#include "datavisualization/graphdock.h"
#include "ui/calendardialog.h"

enum Time {byDay, byMonth, byYear};
enum Field { byCategory = 1, byAccountFrom, byAccountTo, byCreator };

namespace Ui {
class QueryWidget;
}

class QueryWidget : public QWidget
{
    Q_OBJECT
public slots:
    void getField(int);
    void Do ();
    void setupCalendarFrom();
    void setupCalendarTo();
    void setDateFrom();
    void setDateTo();
public:
    explicit QueryWidget(QWidget *parent = 0);
    void setUserman( UserManager *);
    ~QueryWidget();
private:
    Ui::QueryWidget *ui;
    Query * pQuery;
    UserManager * pUserManager;
    CalendarDialog * calendarFrom;
    CalendarDialog * calendarTo;
    QList <QString> names;
    QList <ID> ids;
    std::vector<bool> isSelected;
    int field;
    QMap <ID, QString> nameMap;

    void init();
};

#endif // QUERYWIDGET_H
