#include <QString>
#include <QVector>
#include <logging/logger.h>

#include "util/database_helper.h"
#include "model/currency.h"
#include "dao/currencymanager.h"

ID CurrencyManager::getIdByName(const QString &_name)
{
    int id = -1;
    for(const auto & row : (*db)((select(Currency::TABLE.id))
                                 .from(Currency::TABLE)
                                 .where(Currency::TABLE.name == _name.toStdString()))){
        id = row.id;
    }
    return id;
}

QVector<Currency> CurrencyManager::getAllItems()
{
    QVector<Currency> result;
    int count = 0;
    for(const auto &row : (*db)(select(all_of(Currency::TABLE))
                                .from(Currency::TABLE).unconditionally())){
        logging::debug(std::string("Currency info: id ") + std::to_string(row.id)
                       + ", name " + std::string(row.name)
                       + ", rate " + std::to_string(row.rate));
        Currency newCurrency(row.id,
                     QString::fromStdString(row.name),
                     row.rate);
        result.append(newCurrency);
        count++;
    }
    logging::debug(std::string("") + std::to_string(count) + " currencies in total.");
    return result;
}

ID CurrencyManager::addItem(const Currency &newItem)
{
    logging::debug(std::string("Attempted to add currency with name ")
                               + newItem.name.toStdString()
                               + ", rate "
                               + std::to_string(newItem.rate));
    if(getIdByName(newItem.name) != -1){
        logging::error(std::string("Currency with same name exists: ") + newItem.name.toStdString());
        return -1;
    }
    try{
        (*db)(insert_into(Currency::TABLE).set(
                  Currency::TABLE.name = newItem.name.toStdString(),
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
       (*db)(remove_from(Currency::TABLE).where(
                 Currency::TABLE.id == itemId));
        //TODO remove all items related to this currency
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
                               + std::to_string(newInfo.id)
                               + ", name "
                               + newInfo.name.toStdString()
                               + ", rate "
                               + std::to_string(newInfo.rate));
    try{
        (*db)(update(Currency::TABLE).set(
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
