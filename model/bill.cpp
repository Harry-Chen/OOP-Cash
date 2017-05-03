#include "util/constants.h"
#include "database/tables.h"
#include "model/bill.h"

Table::Bill Bill::TABLE = Table::Bill();

Bill::Bill(ID _id, ID _from, ID _to,
           ID _creator, ID _category, int _quantity,
           ID _currency, QDateTime _ctime, bool _finished,
           QDate _date, QString _note):
    id(_id), from(_from), to(_to), currency(_currency),
    creator(_creator), category(_category), quantity(_quantity),
    ctime(_ctime), finished(_finished), date(_date), note(_note){}

Bill::operator std::string()
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Bill& dt)
{
    os << "Bill info: id " << dt.id
       << ", from " << dt.from
       << ", to " << dt.to
       << ", creator " << dt.creator
       << ", category " << dt.category
       << ", currency " << dt.currency
       << ", quantity " << dt.quantity
       << ", ctime " << dt.ctime.toString().toStdString()
       << ", finished " << dt.finished
       << ", date " << dt.date.toString().toStdString();
    if(!dt.note.isEmpty())
        os << ", note " << dt.note.toStdString();
    return os;
}
