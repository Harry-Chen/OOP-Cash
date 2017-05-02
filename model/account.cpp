#include <QString>
#include <sstream>
#include "util/constants.h"
#include "database/tables.h"
#include "model/account.h"

Account::Account(ID _id, QString _name, ID _uid, ID _cid):
    id(_id), name(_name), uid(_uid), cid(_cid){}
Account::operator std::string()
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

Table::Account Account::TABLE = Table::Account();

std::ostream& operator<<(std::ostream& os, const Account& dt)
{
    os << "Account info: id " << dt.id
       << ", name " << dt.name.toStdString()
       << ", uid " << dt.uid
       << ", cid " << dt.cid;
    return os;
}
