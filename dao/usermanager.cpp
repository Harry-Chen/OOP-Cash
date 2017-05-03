#include "dao/usermanager.h"
#include "model/bill.h"
#include "model/account.h"
#include "model/category.h"
#include "model/currency.h"

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
    logging::debug(std::string("Attempted to login, ")
                   + static_cast<std::string>(User(_user)));
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
        User newUser(row.id,
                     QString::fromStdString(row.username),
                     QString::fromStdString(row.nickname));
        logging::debug(static_cast<std::string>(newUser));
        result.append(newUser);
        count++;
    }
    logging::debug(std::to_string(count) + " users in total.");
    return result;
}

ID UserManager::addItem(const User &newUser)
{
    logging::debug(std::string("Attempted to add user, ")
                   + static_cast<std::string>(User(newUser)));
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
        (*db)(remove_from(Bill::TABLE).where(
                  Bill::TABLE.creator == uid));
        logging::debug(std::string("Sucessfully removed bills of this user."));
        (*db)(remove_from(Account::TABLE).where(
                  Account::TABLE.uid == uid));
        logging::debug(std::string("Sucessfully removed accounts of this user."));
        (*db)(remove_from(Category::TABLE).where(
                  Category::TABLE.uid == uid));
        logging::debug(std::string("Sucessfully removed categories of this user."));
        (*db)(remove_from(Currency::TABLE).where(
                  Currency::TABLE.uid == uid));
        logging::debug(std::string("Sucessfully removed currencies of this user."));
        (*db)(remove_from(User::TABLE).where(
                 User::TABLE.id == uid));
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
    logging::debug(std::string("Attempted to modify user, ")
                               + static_cast<std::string>(User(newInfo)));
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
