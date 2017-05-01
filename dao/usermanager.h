#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>
#include <QVector>
#include "model/user.h"

class User;

class UserManager
{
private:
    static int loggedInUid;
    static int getUidByUsername(const QString &_username);
    static bool validateUsernameAndPassword(User &_user);
public:
    UserManager() = delete;
    static QVector<User> getAllUsers();
    static bool addUser(User &newUser);
    static bool removeUser(const User &userToRemove);
    static bool modifyInfo(User &nowUser, User &newInfo);
    static bool login(User &loginInfo);
    static void logout();
};

#endif // USERMANAGER_H
