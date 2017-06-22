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
 * @file   billadder.cpp
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class BillAdder
 */

#include <QDate>
#include <QDateTime>

#include "billadder.h"

BillAdder::BillAdder(QJsonObject & _obj, UserManager *_userman) : ItemAdder(_obj, _userman) {
    key = "bills";
    accman = new AccountManager(userman);
    catman = new CategoryManager(userman);
    curman = new CurrencyManager(userman);
    billman = new BillManager(userman);
}

bool BillAdder::add(QJsonObject _item) {
    if(!(   _item.contains("accFrom")
            && _item.contains("accTo")
            && _item.contains("catName")
            && _item.contains("curName")
            && _item.contains("quantity")
            && _item.contains("finished")
            && _item.contains("date")
            && _item.contains("note"))) {
        return false;
    }
    auto bill_item = Bill(
                -1,
                accman->getIdByName(_item.take("accFrom").toString()),
                accman->getIdByName(_item.take("accTo").toString()),
                userman->getLoggedInUid(),
                catman->getIdByName(_item.take("catName").toString()),
                _item.take("quantity").toInt(),
                curman->getIdByName(_item.take("curName").toString()),
                QDateTime::currentDateTime(),
                _item.take("finished").toBool(),
                QDate::fromString(_item.take("date").toString(), "yyyy-MM-dd"),
                _item.take("note").toString()
                );
    return ( billman->addItem(bill_item) != -1);
}


