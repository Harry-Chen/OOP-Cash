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
 * @file   accadder.cpp
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class AccAdder
 */

#include "accadder.h"

AccAdder::AccAdder(QJsonObject & _obj, UserManager *_userman) : ItemAdder(_obj, _userman) {
    key = "account";
    accman = new AccountManager(userman);
    curman = new CurrencyManager(userman);
}

bool AccAdder::add(QJsonObject _item) {
    if(!(_item.contains("name") && _item.contains("currency"))) {
        return false;
    }
    auto acc_item = Account(-1, _item.take("name").toString(), userman->getLoggedInUid(), curman->getIdByName( _item.take("currency").toString()));
    return (accman->addItem(acc_item) != -1);
}
