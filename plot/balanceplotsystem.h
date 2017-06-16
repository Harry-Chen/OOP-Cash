#ifndef BALANCEPLOTSYSTEM_H
#define BALANCEPLOTSYSTEM_H

#include "plot/plotsystem.h"
#include "plot/processor/balanceprocessor.h"
#include "plot/plotter/lineplotter.h"

class BalancePlotSystem : public PlotSystem
{
public:
    BalancePlotSystem();
    Processor * createProcessor(const QVector<Bill> & _bills, const QMap<ID, QString> & _nameMap, Plot::Time _time, Plot::Field _field);
    Plotter * createPlotter(const QVector<QString> &_fieldnames, const QVector<QDate> _dates, const QVector<QVector<int> > &_values);
};

#endif // BALANCEPLOTSYSTEM_H
