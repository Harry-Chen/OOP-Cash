/**
 * Copyright 2017 OOP-Cash Team

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   plotsystem.h
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Header file of class PlotSystem
 */

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
