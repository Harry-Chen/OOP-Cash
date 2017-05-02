#include "dao/billmanager.h"

ID BillManager::getIdByName(const QString &_name)
{
    Q_UNUSED(_name);
    throw std::string("Not implemented.");
    return -1;
}

ID BillManager::getIdByCtime(system_clock::time_point _ctime)
{
    int id;
    for(const auto & row : (*db)((select(Bill::TABLE.id))
                                 .from(Bill::TABLE)
                                 .where(Bill::TABLE.ctime == system_clock::to_time_t(_ctime)))){
        id = row.id;
    }
    return id;
}

BillManager::BillManager(UserManager *userMan):
    BillManager(userMan->db)
{
    uid = userMan->loggedInUid;
    if(uid == -1) throw std::string("Not logged in.");
}

QVector<Bill> BillManager::getAllItems()
{
    QVector<Bill> result;
    int count = 0;
    for(const auto &row : (*db)(select(all_of(Bill::TABLE))
                                .from(Bill::TABLE)
                                .where(Bill::TABLE.creator == uid))){
        Bill newBill(row.id, row.afrom, row.ato, row.creator,
                     row.category, row.quantity,
                     system_clock::from_time_t(row.ctime),
                     row.finished,
                     date::floor<days>(system_clock::from_time_t(row.date)),
                     QString::fromStdString(row.note));
        logging::debug(static_cast<std::string>(newBill));
        result.append(newBill);
        count++;
    }
    logging::debug(std::to_string(count) + " bills in total.");
    return result;
}

ID BillManager::addItem(const Bill &newItem)
{
    logging::debug(std::string("Attempted to add bill, ")
                   + static_cast<std::string>(Bill(newItem)));
    if(newItem.creator != uid){
        logging::error(std::string("Can't add bill for other user."));
        return -1;
    }
    try{
        (*db)(insert_into(Bill::TABLE).set(
                  Bill::TABLE.afrom = newItem.from,
                  Bill::TABLE.ato = newItem.to,
                  Bill::TABLE.creator = newItem.creator,
                  Bill::TABLE.category = newItem.category,
                  Bill::TABLE.quantity = newItem.quantity,
                  Bill::TABLE.ctime = system_clock::to_time_t(newItem.ctime),
                  Bill::TABLE.finished = newItem.finished ? 1 : 0,
                  Bill::TABLE.date = system_clock::to_time_t(static_cast<sys_days>(newItem.date)),
                  Bill::TABLE.note = newItem.note.toStdString()));
        int id = getIdByCtime(newItem.ctime);
        logging::debug(std::string("Successfully added bill, id: ") + std::to_string(id));
        return id;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return -1;
    }
}

bool BillManager::removeItemById(const int itemId)
{
    logging::debug(std::string("Attempted to remove bill with id ") + std::to_string(itemId));
    try{
       (*db)(remove_from(Bill::TABLE).where(
                 Bill::TABLE.id == itemId));
        logging::debug(std::string("Sucessfully removed bill."));
        return true;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return false;
    }
}

bool BillManager::modifyItem(const Bill &newInfo)
{
    logging::debug(std::string("Attempted to modify bill, ")
                   + static_cast<std::string>(Bill(newInfo)));
    if(newInfo.creator != uid){
        logging::error(std::string("Can't modify bill for other user."));
        return false;
    }
    try{
        (*db)(update(Bill::TABLE).set(
                  Bill::TABLE.afrom = newInfo.from,
                  Bill::TABLE.ato = newInfo.to,
                  Bill::TABLE.category = newInfo.category,
                  Bill::TABLE.quantity = newInfo.quantity,
                  Bill::TABLE.ctime = system_clock::to_time_t(newInfo.ctime),
                  Bill::TABLE.finished = newInfo.finished ? 1 : 0,
                  Bill::TABLE.date = system_clock::to_time_t(static_cast<sys_days>(newInfo.date)),
                  Bill::TABLE.note = newInfo.note.toStdString())
              .where(Bill::TABLE.id == newInfo.id));
        logging::debug(std::string("Sucessfully modified bill."));
        return true;
    }
    catch(sqlpp::exception e){
        handleSqlException(e);
        return false;
    }
}
