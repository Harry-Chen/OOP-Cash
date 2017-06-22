/**
 * Copyright 2017 OOP-Cash Team

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   user.cpp
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Implementation file of class User
 */

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
