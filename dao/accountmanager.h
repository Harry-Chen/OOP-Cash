#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include <QString>
#include <QVector>
#include "dao/itemmanager.h"
#include "dao/usermanager.h"
#include "model/account.h"

class AccountManager : public ItemManager<Account>
{
private:
    ID uid = -1;
    using ItemManager<Account>::ItemManager;
public:
    AccountManager(UserManager *userMan);
    QMap<ID,Account> getAllItems();
    ID getIdByName(const QString &_name);
    ID addItem(const Account &newItem);
    bool removeItemById(const int itemId);
    bool modifyItem(const Account &newItem);
};

#endif // ACCOUNTMANAGER_H
