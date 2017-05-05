#ifndef CURRENCYMANAGER_H
#define CURRENCYMANAGER_H

#include "dao/itemmanager.h"
#include "dao/usermanager.h"
#include "model/currency.h"

class CurrencyManager : public ItemManager<Currency>
{
private:
    ID uid = -1;
    ID getIdByName(const QString &_name);
    using ItemManager<Currency>::ItemManager;
public:
    CurrencyManager(UserManager *userMan);
    QMap<ID,Currency> getAllItems();
    ID addItem(const Currency &newItem);
    bool removeItemById(const int itemId);
    bool modifyItem(const Currency &newItem);
};

#endif // CURRENCYMANAGER_H
