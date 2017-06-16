#ifndef BILLSPROCESSOR_H
#define BILLSPROCESSOR_H

#include "plot/processor/processor.h"

class BillsProcessor : public Processor
{
    ID (* GetFieldnameptr) (const Bill &);
    QDate (*GetDateptr) (const QDate &);
public:
    //BillsProcessor();
    using Processor::Processor;
    void SetGetFieldname (ID (*func) (const Bill &)) {GetFieldnameptr = func;}
    void SetGetDate (QDate (*func) (const QDate &)) {GetDateptr = func;}
    ID GetFieldname(int i)
    {
        if (GetFieldnameptr)
        return (*GetFieldnameptr) (bills_[i]);
        else return -1; //error
    }
    QDate GetDate(int i)
    {
        if (GetDateptr)
        return(*GetDateptr) (bills_[i].date);
        else return QDate::currentDate(); //error
    }
};

#endif // BILLSPROCESSOR_H
