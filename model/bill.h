#ifndef BILL_H
#define BILL_H

#include <QString>
#include <QDate>
#include <QDateTime>
#include <date.h>
#include "util/constants.h"
#include "database/tables.h"

using namespace date;
using namespace std::chrono;

class Bill
{
public:
    Bill(ID _id = -1, ID _from = -1, ID _to = -1,
         ID _creator = -1, ID _category = -1, int _quantity = 0,
         QDateTime _ctime = QDateTime::currentDateTime(),
         bool _finished = true,
         QDate _date = QDate::currentDate(),
         QString _note = QString());
    ID id;
    ID from;
    ID to;
    ID creator;
    ID category;
    int quantity;
    QDateTime ctime;
    bool finished;
    QDate date;
    QString note;
    operator std::string();
    static Table::Bill TABLE;
    friend std::ostream& operator<<(std::ostream& os, const Bill& dt);
};

#endif // BILL_H
