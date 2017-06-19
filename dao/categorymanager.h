/**
 * Copyright 2017 OOP-Cash Team

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   categorymanager.h
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Header file of class CategoryManager
 */

#ifndef CATEGORYMANAGER_H
#define CATEGORYMANAGER_H

#include <QString>
#include <QVector>
#include "dao/itemmanager.h"
#include "dao/usermanager.h"
#include "model/category.h"

/**
 * @brief manager of Category
 */
class CategoryManager : public ItemManager<Category>
{
private:
    ID uid = -1;
    using ItemManager<Category>::ItemManager;
public:
    /**
     * @brief initiate with UserManager*
     * @param userMan pointer of UserManager that has called login()
     */
    CategoryManager(UserManager *userMan);
    QMap<ID, Category> getAllItems();
    ID getIdByName(const QString &_name);
    ID addItem(const Category &newItem);
    /**
     * @brief remove item with the ID specified
     * @param itemId ID of the item
     * @details every bill using this category will be set to category -1
     */
    bool removeItemById(const int itemId);
    bool modifyItem(const Category &newItem);
};

#endif // CATEGORYMANAGER_H
