#ifndef CURRENCYMANAGER_H
#define CURRENCYMANAGER_H

#include "dao/itemmanager.h"
#include "model/currency.h"

class CurrencyManager : public ItemManager<Currency>
{
private:
    ID getIdByName(const QString &_name);
public:
    using ItemManager<Currency>::ItemManager;
    QVector<Currency> getAllItems();
    ID addItem(const Currency &newItem);
    bool removeItemById(const int itemId);
    bool modifyItem(const Currency &newItem);
};

#endif // CURRENCYMANAGER_H
