#include "processorfactory.h"

ProcessorFactory::ProcessorFactory()
{

}

Processor * ProcessorFactory::creatProcessor(int _time, int _field, Query * pQuery)
{
    time = _time;
    field = _field;
    product = new Processor (pQuery);
    setTime();
    setField();
    return product;
}

void ProcessorFactory::setTime()
{
    switch (time)
    {
    case ProcessorType::byDay:
        product->setIsSameX([](const QDate& date1, const QDate& date2){return date1 == date2;});
        break;
    case ProcessorType::byMonth:
        product->setIsSameX([](const QDate& date1, const QDate& date2){return date1.month() == date2.month() && date1.year() == date2.year();});
        break;
    case ProcessorType::byYear:
        product->setIsSameX([](const QDate& date1, const QDate& date2){return date1.year() == date2.year();});
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
