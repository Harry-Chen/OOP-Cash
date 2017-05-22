#include "processorfactory.h"

#define INIT_DATE 1

ProcessorFactory::ProcessorFactory()
{

}

Processor * ProcessorFactory::creatProcessor(int _time, int _field, Query * pQuery,  const QMap<ID, QString>& _nameMap)
{
    time = _time;
    field = _field;
    product = new Processor (pQuery, _nameMap);
    setTime();
    setField();
    return product;
}

void ProcessorFactory::setTime()
{
    switch (time)
    {
    case ProcessorType::byDay:
        product->setGetX([](QDate date){return date;});
        break;
    case ProcessorType::byWeek:
        product->setGetX([](QDate date){return date;});
        break;
    case ProcessorType::byMonth:
        product->setGetX([](QDate date){return QDate(date.year(),date.month(),INIT_DATE);});
        break;
    case ProcessorType::byYear:
        product->setGetX([](QDate date){return QDate(date.year(),INIT_DATE,INIT_DATE);});
        break;
    default:
        break;
    }
}

void ProcessorFactory::setField()
{
    switch (field)
    {
    case ProcessorType::byCategory:
        product->setGetY([](Bill bill){return bill.category;});
        break;
    case ProcessorType::byAccountFrom:
        product->setGetY([](Bill bill){return bill.from;});
        break;
    case ProcessorType::byAccountTo:
        product->setGetY([](Bill bill){return bill.to;});
        break;
    case ProcessorType::byCreator:
        product->setGetY([](Bill bill){return bill.creator;});
    default:
        break;
    }
}
