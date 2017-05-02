#include <QString>
#include <QVector>
#include <logging/logger.h>

#include "util/database_helper.h"
#include "model/user.h"
#include "dao/usermanager.h"


ID UserManager::getIdByName(const QString &_username)
{
    int uid = -1;
    for(const auto & row : (*db)((select(User::TABLE.id))
                                 .from(User::TABLE)
                                 .where(User::TABLE.username == _username.toStdString()))){
        uid = row.id;
    }
    return uid;
}

bool UserManager::validateUsernameAndPassword(const User &_user)
{
    logging::debug(std::string("Attempted to login with username "
                               + _user.username.toStdString()
                               + " and encrypted password "
                               + _user.encryptedPassword.toStdString()));
    int uid = getIdByName(_user.username);
    if(uid == -1){
        logging::error(std::string("User does not exist: ") + _user.username.toStdString());
        return false;
    }
    for(const auto &row : (*db)(select(User::TABLE.id,
                                       User::TABLE.password)
                                .from(User::TABLE)
                                .where(User::TABLE.id == uid))){
        if(row.password == _user.encryptedPassword.toStdString()){
            logging::debug(std::string("Sucessfully logged in."));
            return true;
        }
    }
    logging::error(std::string("Password not correct."));
    return false;
}

QVector<User> UserManager::getAllItems()
{
    QVector<User> result;
    int count = 0;
    for(const auto &row : (*db)(select(
                                    User::TABLE.id,
                                    User::TABLE.username,
                                    User::TABLE.nickname)
                                .from(User::TABLE).unconditionally())){
        logging::debug(std::string("User info: id ") + std::to_string(row.id)
                       + ", username " + std::string(row.username)
                       + ", nickname " + std::string(row.nickname));
        User newUser(row.id,
                     QString::fromStdString(row.username),
                     QString::fromStdString(row.nickname));
        result.append(newUser);
        count++;
    }
    logging::debug(std::to_string(count) + " users in total.");
    return result;
}

ID UserManager::addItem(const User &newUser)
{
    logging::debug(std::string("Attempted to add user with username "
                               + newUser.username.toStdString()
                               + ", nickname "
                               + newUser.nickname.toStdString()
                               + ", and encrypted password "
                               + newUser.encryptedPassword.toStdString()));
    if(getIdByName(newUser.username) != -1){
        logging::error(std::string("User with same username exists: ") + newUser.username.toStdString());
        return -1;
    }
    try{
        (*db)(insert_into(User::TABLE).set(
                  User::TABLE.username = newUser.username.toStdString(),
                  User::TABLE.nickname = newUser.nickname.toStdString(),
                  User::TABLE.password = newUser.encryptedPassword.toStdString()));
        int uid = getIdByName(newUser.username);
        logging::debug(std::string("Successfully added user, uid: ") + std::to_string(uid));
        return uid;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return -1;
    }
}

bool UserManager::removeItemById(const int uid)
{
    logging::debug(std::string("Attempted to remove user with uid ") + std::to_string(uid));
    if(uid != loggedInUid){
        logging::error(std::string("Not current logged in user."));
        return false;
    }
    try{
       (*db)(remove_from(User::TABLE).where(
                 User::TABLE.id == uid));
        //TODO remove all items related to this user
        logging::debug(std::string("Sucessfully removed user."));
        return true;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return false;
    }
}

bool UserManager::modifyItem(const User &newInfo)
{
    logging::debug(std::string("Attempted to modify user with uid ")
                               + std::to_string(newInfo.id)
                               + ", username "
                               + newInfo.username.toStdString()
                               + ", nickname "
                               + newInfo.nickname.toStdString()
                               + ", and encrypted password "
                               + newInfo.encryptedPassword.toStdString());
    if(newInfo.id != loggedInUid){
        logging::error(std::string("Not current logged in user."));
        return false;
    }
    try{
        (*db)(update(User::TABLE).set(
                  User::TABLE.username = newInfo.username.toStdString(),
                  User::TABLE.nickname = newInfo.nickname.toStdString(),
                  User::TABLE.password = newInfo.encryptedPassword.toStdString())
              .where(User::TABLE.id == newInfo.id));
        logging::debug(std::string("Sucessfully modified user."));
        return true;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return false;
    }
}

ID UserManager::login(const User &loginInfo)
{
    if(validateUsernameAndPassword(loginInfo)){
        loggedInUid = getIdByName(loginInfo.username);
        return loggedInUid;
    }
    return -1;
}

void UserManager::logout(){
    logging::debug(std::string("Logged out."));
    loggedInUid = -1;
}
