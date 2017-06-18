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
 * @file   currencymanager.cpp
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Implementation file of class CurrencyManager
 */

#include "dao/currencymanager.h"
#include "model/bill.h"

ID CurrencyManager::getIdByName(const QString &_name)
{
    int id = -1;
    for(const auto & row : (*db)((select(Currency::TABLE.id))
                                 .from(Currency::TABLE)
                                 .where(Currency::TABLE.name == _name.toStdString()
                                        and (Currency::TABLE.uid == uid)))){
        id = row.id;
    }
    return id;
}

CurrencyManager::CurrencyManager(UserManager *userMan):
    CurrencyManager(userMan->db)
{
    uid = userMan->loggedInUid;
    if(uid == -1) throw std::string("Not logged in.");
}

QMap<ID, Currency> CurrencyManager::getAllItems()
{
    QMap<ID, Currency> result;
    int count = 0;
    for(const auto &row : (*db)(select(all_of(Currency::TABLE))
                                .from(Currency::TABLE)
                                .where(Currency::TABLE.uid == uid
                                       or Currency::TABLE.uid == -1))){
        Currency newCurrency(row.id,
                             row.uid,
                             QString::fromStdString(row.name),
                             row.rate);
        logging::debug(static_cast<std::string>(newCurrency));
        result.insert(row.id, newCurrency);
        count++;
    }
    logging::debug(std::to_string(count) + " currencies in total.");
    return result;
}

ID CurrencyManager::addItem(const Currency &newItem)
{
    logging::debug(std::string("Attempted to add currency, ")
                               + static_cast<std::string>(Currency(newItem)));
    if(getIdByName(newItem.name) != -1){
        logging::error(std::string("Currency with same name exists: ") + newItem.name.toStdString());
        return -1;
    }
    try{
        (*db)(insert_into(Currency::TABLE).set(
                  Currency::TABLE.name = newItem.name.toStdString(),
                  Currency::TABLE.uid = newItem.uid,
                  Currency::TABLE.rate = newItem.rate));
        int id = getIdByName(newItem.name);
        logging::debug(std::string("Successfully added currency, cid: ") + std::to_string(id));
        return id;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return -1;
    }
}

bool CurrencyManager::removeItemById(const int itemId)
{
    logging::debug(std::string("Attempted to remove currency with cid ") + std::to_string(itemId));
    try{
        (*db)(remove_from(Bill::TABLE).where(
                  Bill::TABLE.currency == itemId
                  and Bill::TABLE.creator == uid));
        logging::debug(std::string("Sucessfully removed accounts using this currency."));
        (*db)(remove_from(Currency::TABLE).where(
                 Currency::TABLE.id == itemId));
        logging::debug(std::string("Sucessfully removed currency."));
        return true;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return false;
    }
}

bool CurrencyManager::modifyItem(const Currency &newInfo)
{
    logging::debug(std::string("Attempted to modify currency with cid ")
                               + static_cast<std::string>(Currency(newInfo)));
    if(newInfo.uid != uid){
        logging::error(std::string("Can't modify currency for other user."));
        return false;
    }
    try{
        (*db)(update(Currency::TABLE).set(
                  Currency::TABLE.uid = newInfo.uid,
                  Currency::TABLE.name = newInfo.name.toStdString(),
                  Currency::TABLE.rate = newInfo.rate)
              .where(Currency::TABLE.id == newInfo.id));
        logging::debug(std::string("Sucessfully modified currency."));
        return true;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return false;
    }
}
