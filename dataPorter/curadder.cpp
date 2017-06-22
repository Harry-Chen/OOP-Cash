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
 * @file   curadder.cpp
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class CurAdder
 */

#include "curadder.h"

CurAdder::CurAdder(QJsonObject & _obj, UserManager *_userman) : ItemAdder(_obj, _userman) {
    key = "currency";
    curman = new CurrencyManager(userman);
}

bool CurAdder::add(QJsonObject _item) {
    if(!(_item.contains("name")
         && _item.contains("rate")
      )) {
        return false;
    }
    auto cur_item = Currency(-1, userman->getLoggedInUid(), _item.take("name").toString(), _item.take("rate").toInt(0100));
    return (curman->addItem(cur_item) != -1);
}


