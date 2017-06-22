//抽象工厂类
#ifndef PLOTSYSTEM_H
#define PLOTSYSTEM_H

#include "processor/processor.h"
#include "plotter/plotter.h"
#include "model/bill.h"

#include <QVector>
#include <QString>
#include <QDate>

namespace Plot
{
    enum Time {byDay,byMonth, byYear};
    enum Field { byCategory = 1, byAccountFrom, byAccountTo, byCreater};
}
class PlotSystem
{
protected:

public:
    PlotSystem(){}
    virtual Processor * createProcessor(const QVector<Bill> & _bills, const QMap<ID, QString> & _nameMap, Plot::Time  _time = Plot::byDay, Plot::Field _field = Plot::byCreater) = 0;
    virtual Plotter * createPlotter(const QVector<QString> _fieldnames, const QVector<QDate> _dates, const QVector< QVector<int> > _values ) = 0;
    virtual ~PlotSystem(){}
};

#endif // PLOTSYSTEM_H
