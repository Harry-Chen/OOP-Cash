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
 * @file   billmanager.cpp
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Implementation file of class BillManager
 */

#include "dao/billmanager.h"

ID BillManager::getIdByName(const QString &_name)
{
    Q_UNUSED(_name);
    throw std::string("Not implemented.");
    return -1;
}

ID BillManager::getIdByCtime(const QDateTime &_ctime)
{
    int id;
    for(const auto & row : (*db)((select(Bill::TABLE.id))
                                 .from(Bill::TABLE)
                                 .where(Bill::TABLE.ctime == _ctime.toSecsSinceEpoch()))){
        id = row.id;
    }
    return id;
}

BillManager::BillManager(UserManager *userMan):
    BillManager(userMan->db)
{
    uid = userMan->loggedInUid;
    if(uid == -1) throw std::string("Not logged in.");
}

QMap<ID, Bill> BillManager::getAllItems()
{
    QMap<ID, Bill> result;
    int count = 0;
    for(const auto &row : (*db)(select(all_of(Bill::TABLE))
                                .from(Bill::TABLE)
                                .where(Bill::TABLE.creator == uid))){
        Bill newBill(row.id, row.afrom, row.ato, row.creator,
                     row.category, row.quantity, row.currency,
                     QDateTime::fromSecsSinceEpoch(row.ctime),
                     row.finished,
                     QDate::fromJulianDay(row.date),
                     QString::fromStdString(row.note));
        logging::debug(static_cast<std::string>(newBill));
        result.insert(row.id, newBill);
        count++;
    }
    logging::debug(std::to_string(count) + " bills in total.");
    return result;
}

ID BillManager::addItem(const Bill &newItem)
{
    logging::debug(std::string("Attempted to add bill, ")
                   + static_cast<std::string>(Bill(newItem)));
    if(newItem.creator != uid){
        logging::error(std::string("Can't add bill for other user."));
        return -1;
    }
    try{
        (*db)(insert_into(Bill::TABLE).set(
                  Bill::TABLE.afrom = newItem.from,
                  Bill::TABLE.ato = newItem.to,
                  Bill::TABLE.creator = newItem.creator,
                  Bill::TABLE.category = newItem.category,
                  Bill::TABLE.quantity = newItem.quantity,
                  Bill::TABLE.currency = newItem.currency,
                  Bill::TABLE.ctime = newItem.ctime.toSecsSinceEpoch(),
                  Bill::TABLE.finished = newItem.finished ? 1 : 0,
                  Bill::TABLE.date = newItem.date.toJulianDay(),
                  Bill::TABLE.note = newItem.note.toStdString()));
        int id = getIdByCtime(newItem.ctime);
        logging::debug(std::string("Successfully added bill, id: ") + std::to_string(id));
        return id;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return -1;
    }
}

bool BillManager::removeItemById(const int itemId)
{
    logging::debug(std::string("Attempted to remove bill with id ") + std::to_string(itemId));
    try{
       (*db)(remove_from(Bill::TABLE).where(
                 Bill::TABLE.id == itemId));
        logging::debug(std::string("Sucessfully removed bill."));
        return true;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return false;
    }
}

bool BillManager::modifyItem(const Bill &newInfo)
{
    logging::debug(std::string("Attempted to modify bill, ")
                   + static_cast<std::string>(Bill(newInfo)));
    if(newInfo.creator != uid){
        logging::error(std::string("Can't modify bill for other user."));
        return false;
    }
    try{
        (*db)(update(Bill::TABLE).set(
                  Bill::TABLE.afrom = newInfo.from,
                  Bill::TABLE.ato = newInfo.to,
                  Bill::TABLE.category = newInfo.category,
                  Bill::TABLE.quantity = newInfo.quantity,
                  Bill::TABLE.currency = newInfo.currency,
                  Bill::TABLE.ctime = newInfo.ctime.toSecsSinceEpoch(),
                  Bill::TABLE.finished = newInfo.finished ? 1 : 0,
                  Bill::TABLE.date = newInfo.date.toJulianDay(),
                  Bill::TABLE.note = newInfo.note.toStdString())
              .where(Bill::TABLE.id == newInfo.id));
        logging::debug(std::string("Sucessfully modified bill."));
        return true;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return false;
    }
}
