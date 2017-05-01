#include <QCryptographicHash>
#include "model/user.h"

Table::User User::TABLE = Table::User();

User::User(int _id, QString _username, QString _nickname) : id(_id), username(_username), nickname(_nickname)
{

}

void User::setPassword(const QString &password)
{
    encryptedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex());
}
