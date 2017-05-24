﻿#ifndef CATEGORYMANAGER_H
#define CATEGORYMANAGER_H

#include <QString>
#include <QVector>
#include "dao/itemmanager.h"
#include "dao/usermanager.h"
#include "model/category.h"

class CategoryManager : public ItemManager<Category>
{
private:
    ID uid = -1;
    using ItemManager<Category>::ItemManager;
public:
    CategoryManager(UserManager *_userMan);
    QMap<ID, Category> getAllItems();
    ID getIdByName(const QString &_name);
    ID addItem(const Category &newItem);
    bool removeItemById(const int itemId);
    bool modifyItem(const Category &newItem);
};

#endif // CATEGORYMANAGER_H
