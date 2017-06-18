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
 * @file   bill.cpp
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Implementation file of class Bill
 */

#include "util/constants.h"
#include "database/tables.h"
#include "model/bill.h"

Table::Bill Bill::TABLE = Table::Bill();

Bill::Bill(ID _id, ID _from, ID _to,
           ID _creator, ID _category, int _quantity,
           ID _currency, QDateTime _ctime, bool _finished,
           QDate _date, QString _note):
    id(_id), from(_from), to(_to), currency(_currency),
    creator(_creator), category(_category), quantity(_quantity),
    ctime(_ctime), finished(_finished), date(_date), note(_note){}

Bill::operator std::string()
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Bill& dt)
{
    os << "Bill info: id " << dt.id
       << ", from " << dt.from
       << ", to " << dt.to
       << ", creator " << dt.creator
       << ", category " << dt.category
       << ", currency " << dt.currency
       << ", quantity " << dt.quantity
       << ", ctime " << dt.ctime.toString().toStdString()
       << ", finished " << dt.finished
       << ", date " << dt.date.toString().toStdString();
    if(!dt.note.isEmpty())
        os << ", note " << dt.note.toStdString();
    return os;
}
