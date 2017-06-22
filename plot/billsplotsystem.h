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
 * @file   billsplotsystem.h
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Header file of class BillsPlotSystem
 */

#ifndef BILLSPLOTSYSTEM_H
#define BILLSPLOTSYSTEM_H

#include "plot/plotsystem.h"
#include "plot/processor/billsprocessor.h"
#include "plot/plotter/barplotter.h"

#define INIT_DATE 1 ///< when part of Date is to be ignored, it should be inited with this number

/**
 * @brief The BillsPlotSystem class, an concrete factory
 */
class BillsPlotSystem : public PlotSystem
{
public:
    BillsPlotSystem(){}
    /**
     * @brief create a BillsProcessor
     * @param same with the one in PlotSystem (the base class)
     * @return a pointer to BillsProcessor
     */
    Processor * createProcessor(const QVector<Bill> & _bills, const QMap<ID, QString> & _nameMap, Plot::Time _time, Plot::Field _field);
    /**
     * @brief create a LinePlotter
     * @param same with the one in PlotSystem (the base class)
     * @return a pointer to LinePlotter
     */
    Plotter * createPlotter(const QVector<QString> _fieldnames, const QVector<QDate> _dates, const QVector<QVector<int> > _values);
};

#endif // BILLSPLOTSYSTEM_H
