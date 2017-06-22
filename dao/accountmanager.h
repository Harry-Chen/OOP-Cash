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
 * @file   accountmanager.h
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Header file of class AccountManager
 */


#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QString>
#include <QVector>

#include "dao/itemmanager.h"
#include "dao/usermanager.h"
#include "model/account.h"

/**
 * @brief manager of Account
 */
class AccountManager : public ItemManager<Account>
{
private:
    ID uid = -1;
    using ItemManager<Account>::ItemManager;
public:
    /**
     * @brief initiate with UserManager*
     * @param userMan pointer of UserManager that has called login()
     */
    AccountManager(UserManager *userMan);
    QMap<ID,Account> getAllItems();
    ID getIdByName(const QString &_name);
    ID addItem(const Account &newItem);
    /**
     * @brief remove item with the ID specified
     * @param itemId ID of the item
     * @details WARNING: everything associated with the account will be removed.
     */
    bool removeItemById(const int itemId);
    bool modifyItem(const Account &newItem);
};

#endif // ACCOUNTMANAGER_H
