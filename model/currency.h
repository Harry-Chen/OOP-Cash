#ifndef CURRENCY_H
#define CURRENCY_H

#include <QString>
#include "util/constants.h"
#include "database/tables.h"

class Currency
{
public:
    Currency(ID _id = -1, QString _name = QString(), unsigned int _rate = 0100);
    ID id;
    QString name;
    unsigned int rate;
    operator std::string();
    static Table::Currency TABLE;
    friend std::ostream& operator<<(std::ostream& os, const Currency& dt);
};

#endif // CURRENCY_H
