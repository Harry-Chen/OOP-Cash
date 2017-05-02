#include <QString>
#include <sstream>
#include "util/constants.h"
#include "database/tables.h"
#include "model/user.h"

void User::setPassword(const QString &password){
    if(!password.isNull())
        encryptedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex());
}

User::User(ID _id, QString _username, QString _nickname, QString _password):
    id(_id), username(_username), nickname(_nickname)
{
    setPassword(_password);
}
User::operator std::string()
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

Table::User User::TABLE = Table::User();

std::ostream& operator<<(std::ostream& os, const User& dt)
{
    os << "User info: id " << dt.id
       << ", username " << dt.username.toStdString();
    if(!dt.nickname.isNull())
       os << ", nickname " << dt.nickname.toStdString();
    if(!dt.encryptedPassword.isNull())
       os << ", encryptedPassword " << dt.encryptedPassword.toStdString();
    return os;
}
