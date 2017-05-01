#ifndef USER_H
#define USER_H

#include <QString>
#include "database/tables.h"
#include "dao/usermanager.h"

class User
{
private:
    QString encryptedPassword;
    friend class UserManager;
public:
    User(int _id = -1, QString _username = QString(), QString _nickname = QString());
    int id;
    QString username;
    QString nickname;
    void setPassword(const QString &password);
    static Table::User TABLE;
};

#endif // USER_H
