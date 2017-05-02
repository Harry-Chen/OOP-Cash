#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include "util/constants.h"
#include "database/tables.h"

class Category
{
public:
    Category(ID _id = -1, QString _name = QString(), ID _uid = -1):
        id(_id), name(_name), uid(_uid){}
    ID id;
    QString name;
    ID uid;
    static Table::Category TABLE;
};

#endif // CATEGORY_H
