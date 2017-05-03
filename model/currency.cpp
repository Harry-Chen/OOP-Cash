#include <QString>
#include <sstream>
#include "util/constants.h"
#include "database/tables.h"
#include "model/currency.h"

Currency::Currency(ID _id, ID _uid, QString _name, unsigned int _rate):
    id(_id), uid(_uid), name(_name), rate(_rate){}
Currency::operator std::string()
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

Table::Currency Currency::TABLE = Table::Currency();

std::ostream& operator<<(std::ostream& os, const Currency& dt)
{
    os << "Currency info: id " << dt.id
       << ", uid " << dt.uid
       << ", name " << dt.name.toStdString()
       << ", rate " << dt.rate;
    return os;
}
