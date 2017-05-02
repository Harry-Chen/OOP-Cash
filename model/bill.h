#ifndef BILL_H
#define BILL_H

#include <QString>
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
         system_clock::time_point _ctime = system_clock::now(),
         bool _finished = true,
         year_month_day _date = year_month_day{date::floor<days>(system_clock::now())},
         QString _note = QString());
    ID id;
    ID from;
    ID to;
    ID creator;
    ID category;
    int quantity;
    system_clock::time_point ctime;
    bool finished;
    year_month_day date;
    QString note;
    operator std::string();
    static Table::Bill TABLE;
    friend std::ostream& operator<<(std::ostream& os, const Bill& dt);
};

#endif // BILL_H
