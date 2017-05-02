#include <QString>
#include <sstream>
#include "util/constants.h"
#include "database/tables.h"
#include "model/category.h"

Category::Category(ID _id, QString _name, ID _uid):
    id(_id), name(_name), uid(_uid){}

Category::operator std::string()
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

Table::Category Category::TABLE = Table::Category();

std::ostream& operator<<(std::ostream& os, const Category& dt)
{
    os << "Category info: id " << dt.id
       << ", name " << dt.name.toStdString()
       << ", uid " << dt.uid;
    return os;
}
