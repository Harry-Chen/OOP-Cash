#include "dao/accountmanager.h"

ID AccountManager::getIdByName(const QString &_name)
{
    int id = -1;
    for(const auto & row : (*db)((select(Account::TABLE.id))
                                 .from(Account::TABLE)
                                 .where(Account::TABLE.name == _name.toStdString()
                                        and Account::TABLE.uid == uid))){
        id = row.id;
    }
    return id;
}

AccountManager::AccountManager(UserManager *userMan):
    AccountManager(userMan->db)
{
    uid = userMan->loggedInUid;
    if(uid == -1) throw std::string("Not logged in.");
}

QVector<Account> AccountManager::getAllItems()
{
    QVector<Account> result;
    int count = 0;
    for(const auto &row : (*db)(select(all_of(Account::TABLE))
                                .from(Account::TABLE)
                                .where(Account::TABLE.uid == uid))){
        Account newAccount(row.id,
                     QString::fromStdString(row.name),
                     row.uid,
                     row.cid);
        logging::debug(static_cast<std::string>(newAccount));
        result.append(newAccount);
        count++;
    }
    logging::debug(std::to_string(count) + " accounts in total.");
    return result;
}

ID AccountManager::addItem(const Account &newItem)
{
    logging::debug(std::string("Attempted to add account, ")
                   + static_cast<std::string>(Account(newItem)));
    if(newItem.uid != uid){
        logging::error(std::string("Can't add account for other user."));
        return -1;
    }
    if(getIdByName(newItem.name) != -1){
        logging::error(std::string("Account with same name exists: ") + newItem.name.toStdString());
        return -1;
    }
    try{
        (*db)(insert_into(Account::TABLE).set(
                  Account::TABLE.name = newItem.name.toStdString(),
                  Account::TABLE.uid = newItem.uid,
                  Account::TABLE.cid = newItem.cid));
        int id = getIdByName(newItem.name);
        logging::debug(std::string("Successfully added account, id: ") + std::to_string(id));
        return id;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return -1;
    }
}

bool AccountManager::removeItemById(const int itemId)
{
    logging::debug(std::string("Attempted to remove account with id ") + std::to_string(itemId));
    try{
        //TODO remove all bills related to this account
       (*db)(remove_from(Account::TABLE).where(
                 Account::TABLE.id == itemId));
        logging::debug(std::string("Sucessfully removed account."));
        return true;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return false;
    }
}

bool AccountManager::modifyItem(const Account &newInfo)
{
    logging::debug(std::string("Attempted to modify account, ")
                   + static_cast<std::string>(Account(newInfo)));
    if(newInfo.uid != uid){
        logging::error(std::string("Can't modify account for other user."));
        return false;
    }
    try{
        (*db)(update(Account::TABLE).set(
                  Account::TABLE.name = newInfo.name.toStdString(),
                  Account::TABLE.uid = newInfo.uid,
                  Account::TABLE.cid = newInfo.cid)
              .where(Account::TABLE.id == newInfo.id));
        logging::debug(std::string("Sucessfully modified account."));
        return true;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return false;
    }
}
