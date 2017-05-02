#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <sstream>
#include "util/constants.h"
#include "database/tables.h"

class Account
{
public:
    Account(ID _id = -1, QString _name = QString(), ID _uid = -1, ID _cid = -1);
    ID id;
    QString name;
    ID uid;
    ID cid;
    operator std::string();
    friend std::ostream& operator<<(std::ostream& os, const Account& dt);
    static Table::Account TABLE;
};

#endif // ACCOUNT_H
