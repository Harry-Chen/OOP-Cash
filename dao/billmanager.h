#ifndef BILLMANAGER_H
#define BILLMANAGER_H

#include <QString>
#include <QVector>
#include <QDate>
#include <QDateTime>

#include "dao/itemmanager.h"
#include "dao/usermanager.h"
#include "dao/billmanager.h"
#include "model/bill.h"

class BillManager : public ItemManager<Bill>
{
private:
    ID uid = -1;
    ID getIdByName(const QString &_name);
    ID getIdByCtime(const QDateTime &_ctime);
    using ItemManager<Bill>::ItemManager;
public:
    BillManager(UserManager *userMan);
    QVector<Bill> getAllItems();
    ID addItem(const Bill &newItem);
    bool removeItemById(const int itemId);
    bool modifyItem(const Bill &newItem);
};

#endif // BILLMANAGER_H
