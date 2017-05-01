#include <QString>
#include <QVector>
#include <logging/logger.h>

#include "util/database_helper.h"
#include "database/tables.h"
#include "model/user.h"
#include "dao/usermanager.h"

int UserManager::loggedInUid = -1;

int UserManager::getUidByUsername(const QString &_username)
{
    int uid = -1;
    for(const auto & row : (*DatabaseHelper::getDb())((select(User::TABLE.id))
                                                      .from(User::TABLE)
                                                      .where(User::TABLE.username == _username.toStdString()))){
        uid = row.id;
    }
    return uid;
}

bool UserManager::validateUsernameAndPassword(User &user)
{
    int uid = getUidByUsername(user.username);
    if(uid == -1) return false;
    for(const auto &row : (*DatabaseHelper::getDb())(select(User::TABLE.id,
                                                            User::TABLE.password)
                                                     .from(User::TABLE)
                                                     .where(User::TABLE.id == uid))){
        if(row.password == user.encryptedPassword.toStdString()){
            user.id = row.id;
            return true;
        }
    }
    return false;
}

QVector<User> UserManager::getAllUsers()
{
    QVector<User> result;
    for(const auto &row : (*DatabaseHelper::getDb())(select(
                                                         User::TABLE.id,
                                                         User::TABLE.username,
                                                         User::TABLE.nickname)
                                                     .from(User::TABLE).unconditionally())){
        User newUser(row.id, QString::fromStdString(row.username), QString::fromStdString(row.nickname));
        result.append(newUser);
    }
    return result;
}

bool UserManager::addUser(User &newUser)
{
    if(getUidByUsername(newUser.username) != -1){
        return false;
    }
    try{
        (*DatabaseHelper::getDb())(insert_into(User::TABLE).set(
                                       User::TABLE.username = newUser.username.toStdString(),
                                       User::TABLE.nickname = newUser.nickname.toStdString(),
                                       User::TABLE.password = newUser.encryptedPassword.toStdString()));
        newUser.id = getUidByUsername(newUser.username);
        return true;
    }
    catch(sqlpp::exception e){
        logging::error(std::string("SQL Error:\n") + e.what());
        return false;
    }
}

bool UserManager::removeUser(const User &userToRemove)
{
    if(getUidByUsername(userToRemove.username) != userToRemove.id){
        return false;
    }
    try{
       (*DatabaseHelper::getDb())(remove_from(User::TABLE).where(
                                       User::TABLE.id == userToRemove.id));
        return true;
    }
    catch(sqlpp::exception e){
        logging::error(std::string("SQL Error:\n") + e.what());
        return false;
    }
}

bool UserManager::modifyInfo(User &nowUser, User &newInfo)
{
    if(validateUsernameAndPassword(nowUser)){
        try{
            (*DatabaseHelper::getDb())(update(User::TABLE).set(
                                       User::TABLE.nickname = newInfo.nickname.toStdString(),
                                       User::TABLE.password = newInfo.encryptedPassword.toStdString())
                                   .where(User::TABLE.id == nowUser.id));
            newInfo.id = nowUser.id;
            return true;
        }
        catch(sqlpp::exception e){
            logging::error(std::string("SQL Error:\n") + e.what());
            return false;
        }
    }
    else{
        return false;
    }
}

bool UserManager::login(User &loginInfo)
{
    if(validateUsernameAndPassword(loginInfo)){
        UserManager::loggedInUid = getUidByUsername(loginInfo.username);
        return true;
    }
    else return false;
}

void UserManager::logout(){
    UserManager::loggedInUid = -1;
}
