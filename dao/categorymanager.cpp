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
 * @file   categorymanager.cpp
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Implementation file of class CategoryManager
 */

#include "dao/categorymanager.h"
#include "model/bill.h"

ID CategoryManager::getIdByName(const QString &_name)
{
    int id = -1;
    for(const auto & row : (*db)((select(Category::TABLE.id))
                                 .from(Category::TABLE)
                                 .where(Category::TABLE.name == _name.toStdString()
                                        and (Category::TABLE.uid == uid)))){
        id = row.id;
    }
    return id;
}

CategoryManager::CategoryManager(UserManager *userMan):
    CategoryManager(userMan->db)
{
    uid = userMan->loggedInUid;
    if(uid == -1) throw std::string("Not logged in.");
}

QMap<ID, Category> CategoryManager::getAllItems()
{
    QMap<ID, Category> result;
    int count = 0;
    for(const auto &row : (*db)(select(all_of(Category::TABLE))
                                .from(Category::TABLE)
                                .where(Category::TABLE.uid == uid
                                       or Category::TABLE.uid == -1))){
        Category newCategory(row.id,
                     QString::fromStdString(row.name),
                     row.uid);
        logging::debug(static_cast<std::string>(newCategory));
        result.insert(row.id, newCategory);
        count++;
    }
    logging::debug(std::to_string(count) + " categories in total.");
    return result;
}

ID CategoryManager::addItem(const Category &newItem)
{
    logging::debug(std::string("Attempted to add category, ")
                   + static_cast<std::string>(Category(newItem)));
    if(newItem.uid != uid){
        logging::error(std::string("Can't add category for other user."));
        return -1;
    }
    if(getIdByName(newItem.name) != -1){
        logging::error(std::string("Category with same name exists: ") + newItem.name.toStdString());
        return -1;
    }
    try{
        (*db)(insert_into(Category::TABLE).set(
                  Category::TABLE.name = newItem.name.toStdString(),
                  Category::TABLE.uid = newItem.uid));
        int id = getIdByName(newItem.name);
        logging::debug(std::string("Successfully added category, id: ") + std::to_string(id));
        return id;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return -1;
    }
}

bool CategoryManager::removeItemById(const int itemId)
{
    logging::debug(std::string("Attempted to remove category with id ") + std::to_string(itemId));
    try{
        (*db)(update(Bill::TABLE).set(
                  Bill::TABLE.category = -1
                  )
              .where(Bill::TABLE.category == itemId
                     and Bill::TABLE.creator == uid));
        logging::debug(std::string("Sucessfully updated all bills using this category."));
        (*db)(remove_from(Category::TABLE).where(
                 Category::TABLE.id == itemId));
        logging::debug(std::string("Sucessfully removed category."));
        return true;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return false;
    }
}

bool CategoryManager::modifyItem(const Category &newInfo)
{
    logging::debug(std::string("Attempted to modify category, ")
                   + static_cast<std::string>(Category(newInfo)));
    if(newInfo.uid != uid){
        logging::error(std::string("Can't modify category for other user."));
        return false;
    }
    try{
        (*db)(update(Category::TABLE).set(
                  Category::TABLE.name = newInfo.name.toStdString(),
                  Category::TABLE.uid = newInfo.uid)
              .where(Category::TABLE.id == newInfo.id));
        logging::debug(std::string("Sucessfully modified category."));
        return true;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return false;
    }
}
