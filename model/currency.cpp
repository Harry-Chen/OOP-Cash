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
 * @file   currency.cpp
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Implementation file of class Currency
 */

#include <QString>
#include <sstream>
#include "util/constants.h"
#include "database/tables.h"
#include "model/currency.h"

Currency::Currency(ID _id, ID _uid, QString _name, unsigned int _rate):
    id(_id), uid(_uid), name(_name), rate(_rate){}
Currency::operator std::string()
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

Table::Currency Currency::TABLE = Table::Currency();

std::ostream& operator<<(std::ostream& os, const Currency& dt)
{
    os << "Currency info: id " << dt.id
       << ", uid " << dt.uid
       << ", name " << dt.name.toStdString()
       << ", rate " << dt.rate;
    return os;
}
