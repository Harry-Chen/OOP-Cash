#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QVector>
#include <QMap>
#include "model/bill.h"
#include "dao/query.h"
#include "process/processorbase.h"

class Processor :public ProcessorBase
{
    //bool (* isSameXptr) (const QDate&, const QDate&);
    ID (* getYptr) (Bill);
    QDate (*getXptr) (QDate);

   // int num; //即Y.size, 表示y(x)的个数, 0表示单变量，-1表示因变量个数未知， 正值表示因变量个数
public:
    Processor (const QVector<Bill> &, const QMap<ID, QString> & _nameMap);
    // double timeSpan;
    ID getY(int i) { return (*getYptr) (raw[i]);}
    QDate getX(int i) {return(*getXptr) (raw[i].date);}
    //bool isSameX (QDate date1, QDate date2) {
    //return (*isSameXptr)(date1, date2);}
    //bool isSameY (int i1, int i2);

    //bool processAll();

    //void setIsSameX (bool (*func) (const QDate&, const QDate&)) {isSameXptr = func;}
    void setGetY (ID (*func) (Bill)) {getYptr = func;}
    void setGetX (QDate (*func) (QDate)) {getXptr = func;}
    //QVector <QString> getYvector();
};

#endif // PROCESSOR_H
