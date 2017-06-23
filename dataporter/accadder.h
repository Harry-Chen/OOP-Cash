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
 * @file   accadder.h
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Header file of class AccAdder
 */

#ifndef ACCADDER_H
#define ACCADDER_H

#include "dao/accountmanager.h"
#include "dao/currencymanager.h"
#include "model/account.h"
#include "itemadder.h"

/**
 * @brief the adder of Account
 */
class AccAdder : public ItemAdder
{
    AccountManager * accman;
    CurrencyManager * curman;

public:
    /**
     * @brief Initiate with QJsonObject& and UserManager*
     * @param _obj reference to the QJsonObject of DataImporter
     * @param _userman pointer of UserManager in charge of the User who has loggedin.
     */
    AccAdder(QJsonObject & _obj, UserManager* _userman);
    /**
     * @brief function to add an Account
     * @param _item the account in type of QJsonObject
     * @return succeeded or not
     */
    bool add(QJsonObject _item);
};

#endif // ACCADDER_H
