#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>
#include <QVector>
#include "dao/itemmanager.h"
#include "model/user.h"

class User;

class UserManager: public ItemManager<User>
{
    friend class AccountManager;
    friend class CategoryManager;
    friend class CurrencyManager;
    friend class BillManager;
private:
    ID loggedInUid;
    ID getIdByName(const QString &_name);
    bool validateUsernameAndPassword(const User &_user);
public:
    using ItemManager<User>::ItemManager;
    QMap<ID, User> getAllItems();
    ID addItem(const User &newItem);
    bool removeItemById(const int itemId);
    bool modifyItem(const User &newItem);
    ID login(const User& loginInfo);
    void logout();
};

#endif // USERMANAGER_H
