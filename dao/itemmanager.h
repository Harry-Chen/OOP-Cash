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
 * @file   itemmanager.h
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Header file of class ItemManager<T>
 */

#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <QMap>
#include <logging/logger.h>
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/sqlite3/connection.h>

#include "util/constants.h"

/**
 * @brief Abstract manager of items
 */
template <typename T>
class ItemManager
{
protected:
    sqlpp::sqlite3::connection *db;
    void handleSqlException(sqlpp::exception e){
        logging::error(std::string("Error occured while executing SQL statement:\n") + e.what());
    }
public:
    ItemManager() = delete;
    /**
     * @brief initiate with db connection
     * @param _db database connection
     */
    ItemManager(sqlpp::sqlite3::connection *_db):db(_db){}
    /**
     * @brief get all items of T in the database
     * @return QMap of items, with ID as key
     */
    virtual QMap<ID,T> getAllItems() = 0;
    /**
     * @brief get the ID of item by name
     * @param _name name of the item
     * @return ID of the item, -1 if not found
     */
    virtual ID getIdByName(const QString &_name) = 0;
    /**
     * @brief insert one new item into the databse
     * @param newItem new item
     * @return ID if successful, -1 if not
     */
    virtual ID addItem(const T &newItem) = 0;
    /**
     * @brief remove item with the ID specified
     * @param itemId ID of the item
     * @return true if successful, false if not
     */
    virtual bool removeItemById(const int itemId) = 0;
    /**
     * @brief modify the content of item in the database
     * @param newItem the modified item
     * @return true if successful, false if not
     *
     * The item can only be modified with an existed ID.
     */
    virtual bool modifyItem(const T &newItem) = 0;
};


#endif // ITEMMANAGER_H
