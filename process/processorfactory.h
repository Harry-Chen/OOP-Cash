#ifndef PROCESSORFACTORY_H
#define PROCESSORFACTORY_H

#include <QVector>
#include "process/processor.h"
#include "model/bill.h"
#include <QMessageBox>

namespace ProcessorType
{
    enum Time {byDay,byMonth, byYear};
    enum Field { byCategory = 1, byAccountFrom, byAccountTo, byCreator };
}

class ProcessorFactory
{
    int time;
    int field;

    Processor * product;
public:
    ProcessorFactory();
    ProcessorBase * creatProcessor(int, int, const QVector<Bill> &, const QMap<ID, QString> & );
    void setTime();
    void setField();
};

#endif // PROCESSORFACTORY_H
