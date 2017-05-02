#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include "util/constants.h"
#include "database/tables.h"

class Category
{
public:
    Category(ID _id = -1, QString _name = QString(), ID _uid = -1);
    ID id;
    QString name;
    ID uid;
    operator std::string();
    static Table::Category TABLE;
    friend std::ostream& operator<<(std::ostream& os, const Category& dt);
};

#endif // CATEGORY_H
