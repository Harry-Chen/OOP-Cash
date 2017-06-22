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
 * @file   usermanager.h
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Header file of class UserManager
 */

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>
#include <QVector>

#include "dao/itemmanager.h"
#include "model/user.h"

class User;

/**
 * @brief manager of User
 */
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
    /**
     * @brief add new user
     * @param newItem infomation of new user
     * @return ID if successful, -1 if not
     * @details The operation will fail if username is the same with another existed user.
     */
    ID addItem(const User &newItem);
    /**
     * @brief remove item with the ID specified
     * @param itemId ID of the item
     * @details WARNING: everything associated with the user will be removed.
     */
    bool removeItemById(const int itemId);
    bool modifyItem(const User &newItem);
    /**
     * @brief login with specific username and password
     * @param loginInfo User object filled with login information
     * @return ID if successful, -1 if not
     */
    ID login(const User& loginInfo);
    /**
     * @brief log out
     * @details must be called after successfully calling login()
     */
    void logout();
    /**
     * @return the UID of the user currently loggedin
     * @details behaviour undefined if called before calling login()
     */
	ID getLoggedInUid() { return loggedInUid; }
};

#endif // USERMANAGER_H
