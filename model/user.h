﻿/**
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
 * @file   user.h
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Header file of class User
 */

#ifndef USER_H
#define USER_H

#include <QString>
#include <QCryptographicHash>

#include "database/tables.h"
#include "dao/usermanager.h"

/**
 * @brief data model of User
 */
class User
{
    friend class UserManager;
private:
    QString encryptedPassword;

public:
    /**
     * @brief Constructor
     * @param _id UID, can be -1 if unknown
     * @param _username user name
     * @param _nickname nick name (can be empty)
     * @param _password password
     * @details automatically call setPassword() with the given password
     */
    User(ID _id = -1, QString _username = QString(), QString _nickname = QString(), QString _password = QString());
    ID id;
    QString username;
    QString nickname;
    operator std::string();
    static Table::User TABLE; ///< for ORM usage
    friend std::ostream& operator<<(std::ostream& os, const User& dt);
    /**
     * @brief set (encrypted) password for user
     * @details the password will be MD5 hashed before stored
     * @param password the unencrypted password
     */
    void setPassword(const QString &password);
};

#endif // USER_H
