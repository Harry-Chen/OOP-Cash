#ifndef QUERYWIDGET_H
#define QUERYWIDGET_H

#include <QWidget>
#include <QString>
#include "dao/query.h"
#include "process/processor.h"
#include "process/processorfactory.h"
#include "dao/usermanager.h"
#include "dao/currencymanager.h"
#include "dao/accountmanager.h"
#include "dao/categorymanager.h"
#include "dao/billmanager.h"
#include "util/database_helper.h"

enum Time {byDay, byWeek, byMonth, byYear};
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
public:
    explicit QueryWidget(QWidget *parent = 0);
    void setUserman( UserManager *);
    ~QueryWidget();

private:
    Ui::QueryWidget *ui;
    Query * pQuery;
    Processor * pProcessor;
    UserManager * pUserManager;
    QList <QString> names;
    QList <ID> ids;
    //template <typename T> QMap<ID,T> map;
    std::vector<bool> isSelected;
    //void getList (int);//填充Ids和names
    //void setList ();//按Ids
};

#endif // QUERYWIDGET_H
