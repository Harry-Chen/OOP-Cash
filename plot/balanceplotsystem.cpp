#include "balanceplotsystem.h"

BalancePlotSystem::BalancePlotSystem()
{

}

Processor * BalancePlotSystem::createProcessor(const QVector<Bill> &_bills, const QMap<ID, QString> &_nameMap, Plot::Time _time, Plot::Field _field)
{
    return new BalanceProcessor(_bills, _nameMap);
}

Plotter * BalancePlotSystem::createPlotter(const QVector<QString> &_fieldnames, const QVector<QDate> _dates, const QVector<QVector<int> > &_values)
{
    return new LinePlotter(_fieldnames, _dates, _values);
}
