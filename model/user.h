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
    void setPassword(const QString &password){
        encryptedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex());
    }
public:
    User(int _id = -1, QString _username = QString(), QString _nickname = QString(), QString _password = QString()):
        id(_id), username(_username), nickname(_nickname)
    {
        setPassword(_password);
    }
    int id;
    QString username;
    QString nickname;
    static Table::User TABLE;
};

#endif // USER_H
