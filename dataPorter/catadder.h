#ifndef CATADDER_H
#define CATADDER_H
#include "itemadder.h"
#include "dao/categorymanager.h"
#include "model/category.h"

class catAdder : public itemAdder
{
    CategoryManager * catman;
public:
    catAdder(QJsonObject & _obj, UserManager* _userman);
    bool add(QJsonObject & _item);
};

#endif // CATADDER_H
