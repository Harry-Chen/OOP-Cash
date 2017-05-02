#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include "util/constants.h"
#include "database/tables.h"

class Account
{
public:
    Account(ID _id = -1, QString _name = QString(), ID _uid = -1, ID _cid = -1):
        id(_id), name(_name), uid(_uid), cid(_cid){}
    ID id;
    QString name;
    ID uid;
    ID cid;
    static Table::Account TABLE;
};

#endif // ACCOUNT_H
