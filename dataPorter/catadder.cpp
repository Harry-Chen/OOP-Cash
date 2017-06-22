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
 * @file   catadder.cpp
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class CatAdder
 */

#include "catadder.h"

CatAdder::CatAdder(QJsonObject &_obj, UserManager *_userman): ItemAdder(_obj, _userman) {
    key = "category";
    catman = new CategoryManager(userman);
}

bool CatAdder::add(QJsonObject _item) {
    if(!(_item.contains("name"))) {
        return false;
    }
    auto cat_item = Category(-1,_item.take("name").toString(), userman->getLoggedInUid());
    return (catman->addItem(cat_item) != -1);
}
