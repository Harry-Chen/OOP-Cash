#ifndef BILLSPLOTSYSTEM_H
#define BILLSPLOTSYSTEM_H

#include "plot/plotsystem.h"
#include "plot/processor/billsprocessor.h"
#include "plot/plotter/barplotter.h"

#define INIT_DATE 1

class BillsPlotSystem : public PlotSystem
{
public:
    BillsPlotSystem();
    Processor * createProcessor(const QVector<Bill> & _bills, const QMap<ID, QString> & _nameMap, Plot::Time _time, Plot::Field _field);
    Plotter * createPlotter(const QVector<QString> &_fieldnames, const QVector<QDate> _dates, const QVector<QVector<int> > &_values);
};

#endif // BILLSPLOTSYSTEM_H
