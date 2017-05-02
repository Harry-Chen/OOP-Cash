#ifndef CURRENCY_H
#define CURRENCY_H

#include <QString>
#include "util/constants.h"
#include "database/tables.h"

class Currency
{
public:
    Currency(int _id = -1, QString _name = QString(), unsigned int _rate = 0100):
        id(_id), name(_name), rate(_rate){}
    ID id;
    QString name;
    unsigned int rate;
    static Table::Currency TABLE;
};

#endif // CURRENCY_H
