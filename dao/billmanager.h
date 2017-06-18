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
 * @file   bill.h
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Header file of class BillManager
 */

#ifndef BILLMANAGER_H
#define BILLMANAGER_H

#include <QString>
#include <QVector>
#include <QDate>
#include <QDateTime>

#include "dao/itemmanager.h"
#include "dao/usermanager.h"
#include "dao/billmanager.h"
#include "model/bill.h"

/**
 * @brief manager of Bill
 */
class BillManager : public ItemManager<Bill>
{
private:
    ID uid = -1;
    ID getIdByCtime(const QDateTime &_ctime);
    using ItemManager<Bill>::ItemManager;
public:
    /**
     * @brief initiate with UserManager*
     * @param userMan pointer of UserManager that has called login()
     */
    BillManager(UserManager *userMan);
    QMap<ID,Bill> getAllItems();
    ID getIdByName(const QString &_name);
    ID addItem(const Bill &newItem);
    bool removeItemById(const int itemId);
    bool modifyItem(const Bill &newItem);
};

#endif // BILLMANAGER_H
