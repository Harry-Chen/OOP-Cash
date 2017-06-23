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
 * @file   balanceplotsystem.h
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Header file of class BalancePlotSystem
 */

#ifndef BALANCEPLOTSYSTEM_H
#define BALANCEPLOTSYSTEM_H

#include "plotsystem.h"
#include "plot/processor/balanceprocessor.h"
#include "plot/plotter/lineplotter.h"

/**
 * @brief The BalancePlotSystem class, a concrete factory, produce a BalanceProcessor and a LinePlotter
 */
class BalancePlotSystem : public PlotSystem
{
public:
    BalancePlotSystem(){}
    Processor * createProcessor(const QVector<Bill> & _bills, const QMap<ID, QString> & _nameMap, Plot::Time _time, Plot::Field _field);
    Plotter * createPlotter(const QVector<QString> _fieldnames, const QVector<QDate> _dates, const QVector<QVector<int> > _values);
};

#endif // BALANCEPLOTSYSTEM_H
