#ifndef PROCESSORFACTORY_H
#define PROCESSORFACTORY_H

#include <QVector>
#include "process/processor.h"
#include "model/bill.h"

namespace ProcessorType
{
    enum Time {byDay, byWeek, byMonth, byYear};
    enum Field { byCategory, byAccountFrom, byAccountTo };
}

class ProcessorFactory : public Processor
{
    ProcessorType::Time time;
    ProcessorType::Field field;
    Processor * product;
public:
    ProcessorFactory();
    Processor * creatProcessor(int, int, const QVector <Bill>);
    void setTime();
    void setField();
};

#endif // PROCESSORFACTORY_H
