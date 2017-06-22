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
 * @file   dataexporter.h
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Header file of class DataExporter
 */

#ifndef DATAEXPORTER_H
#define DATAEXPORTER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

#include "dao/usermanager.h"
#include "dao/accountmanager.h"
#include "dao/billmanager.h"
#include "dao/categorymanager.h"
#include "dao/currencymanager.h"
#include "dao/query.h"
#include "model/user.h"
#include "model/account.h"
#include "model/bill.h"
#include "model/category.h"
#include "model/currency.h"

/**
 * @brief The DataExporter class
 */
class DataExporter {
private:
    UserManager * userman;
    AccountManager * accman;
    CategoryManager * catman;
    CurrencyManager * curman;
    QMap<ID, User> userMap;
    QMap<ID, Account> accMap;
    QMap<ID, Category> catMap;
    QMap<ID, Currency> curMap;
    QVector<Bill> exportBills;
    QJsonArray getBillArray(QVector<Bill>&);
    QJsonArray getCurrencyArray();
    QJsonArray getAccountArray();
    QJsonArray getCategoryArray();

public:
    /**
     * @brief Initiate with UserManager*
     * @param _userman pointer of UserManager in charge of the User who has loggedin.
     */
    DataExporter(UserManager * _userman);
    /**
     * @brief doExport
     * @return Export succeeded or not
     */
    bool doExport();
};

#endif // DATAEXPORTER_H
