#ifndef PROCESSORFACTORY_H
#define PROCESSORFACTORY_H

#include <QVector>
#include "process/processor.h"
#include "model/bill.h"

namespace ProcessorType
{
    enum Time {byDay, byWeek, byMonth, byYear};
    enum Field { byCategory, byAccountFrom, byAccountTo, byCreator };
}

class ProcessorFactory
{
    int time;
    int field;
    Processor * product;
public:
    ProcessorFactory();
    Processor * creatProcessor(int, int, Query *);
    void setTime();
    void setField();
};

#endif // PROCESSORFACTORY_H
