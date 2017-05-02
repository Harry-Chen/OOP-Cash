#ifndef USER_H
#define USER_H

#include <QString>
#include <QCryptographicHash>
#include "database/tables.h"
#include "dao/usermanager.h"

class User
{
    friend class UserManager;
private:
    QString encryptedPassword;
    void setPassword(const QString &password);
public:
    User(ID _id = -1, QString _username = QString(), QString _nickname = QString(), QString _password = QString());
    ID id;
    QString username;
    QString nickname;
    operator std::string();
    static Table::User TABLE;
    friend std::ostream& operator<<(std::ostream& os, const User& dt);
};

#endif // USER_H
