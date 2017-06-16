#include "billsplotsystem.h"

BillsPlotSystem::BillsPlotSystem()
{

}

Processor * BillsPlotSystem::createProcessor(const QVector<Bill> &_bills, const QMap<ID, QString> &_nameMap, Plot::Time _time, Plot::Field _field)
{
    BillsProcessor * pProcessor = new BillsProcessor ( _bills, _nameMap);
    switch (_time)
    {
    case Plot::byDay:
        pProcessor->SetGetDate([](const QDate & date){return date;});
        break;
    case Plot::byMonth:
        pProcessor->SetGetDate([](const QDate & date){return QDate(date.year(),date.month(),INIT_DATE);});
        break;
    case Plot::byYear:
        pProcessor->SetGetDate([](const QDate & date){return QDate(date.year(),INIT_DATE,INIT_DATE);});
        break;
    default:
        break;
    }

    switch (_field)
    {
    case Plot::byCategory:
        pProcessor->SetGetFieldname([](const Bill & bill){return bill.category;});
        break;
    case Plot::byAccountFrom:
        pProcessor->SetGetFieldname([](const Bill & bill){return bill.from;});
        break;
    case Plot::byAccountTo:
        pProcessor->SetGetFieldname([](const Bill & bill){return bill.to;});
        break;
    default:
        //QMessageBox()
        break;
    }
    return dynamic_cast<Processor *> (pProcessor);
}

Plotter * BillsPlotSystem::createPlotter(const QVector<QString> &_fieldnames, const QVector<QDate> _dates, const QVector<QVector<int> > &_values)
{
    return new BillsPlotter(_fieldnames, _dates, _values);
}
