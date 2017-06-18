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
 * @file   currencymanager.h
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Header file of class CurrencyManager
 */

#ifndef CURRENCYMANAGER_H
#define CURRENCYMANAGER_H

#include "dao/itemmanager.h"
#include "dao/usermanager.h"
#include "model/currency.h"

/**
 * @brief manager of Currency
 */
class CurrencyManager : public ItemManager<Currency>
{
private:
    ID uid = -1;
    using ItemManager<Currency>::ItemManager;
public:
    /**
     * @brief initiate with UserManager*
     * @param userMan pointer of UserManager that has called login()
     */
    CurrencyManager(UserManager *userMan);
    QMap<ID,Currency> getAllItems();
    ID getIdByName(const QString &_name);
    ID addItem(const Currency &newItem);
    /**
     * @brief remove item with the ID specified
     * @param itemId ID of the item
     * @details WARNING: all Accounts associated with the user will be removed.
     */
    bool removeItemById(const int itemId);
    bool modifyItem(const Currency &newItem);
};

#endif // CURRENCYMANAGER_H
