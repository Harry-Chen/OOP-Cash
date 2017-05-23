#include "processor.h"
/*
ID Processor::getY(int i)
{
    return gety->getY(raw[i]);
}

bool isSame(bool (*func)(const QDate&, const QDate&), const QDate& a, const QDate& b){
    return (*func)(a, b);
}

void compare(){
    QDate a, b;
    bool sameYear = isSame([](const QDate& a1, const QDate& a2){return a1.year() == a2.year();}, a, b);

}

bool Processor::isSameX(int i1, int i2)
{
    return isSameX(raw[i1].date, X[i2]);
}
*/

Processor::Processor(const QVector<Bill> &bills, const QMap<ID, QString> &_nameMap)
{
    raw = bills;
    nameMap = _nameMap;
    X.clear();
    Y.clear();
    QVector<int> temp(1,0);
    matrix.push_back(temp);
    X.push_back(QDate());
    Y.push_back(0);
   // std::cout << raw.size() << std::endl;
}


