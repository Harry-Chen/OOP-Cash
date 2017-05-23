#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <QMap>
#include <logging/logger.h>
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/sqlite3/connection.h>

#include "util/constants.h"

template <typename T>
class ItemManager
{
protected:
    sqlpp::sqlite3::connection *db;
    void handleSqlException(sqlpp::exception e){
        logging::error(std::string("Error occured while executing SQL statement:\n") + e.what());
    }
public:
    ItemManager() = delete;
    ItemManager(sqlpp::sqlite3::connection *_db):db(_db){}
    virtual QMap<ID,T> getAllItems() = 0;
    virtual ID getIdByName(const QString &_name) = 0;
    virtual ID addItem(const T &newItem) = 0;
    virtual bool removeItemById(const int itemId) = 0;
    virtual bool modifyItem(const T &newItem) = 0;
};


#endif // ITEMMANAGER_H
