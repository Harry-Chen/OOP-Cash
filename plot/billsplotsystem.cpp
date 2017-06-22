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
 * @file   billsplotsystem.cpp
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Implementation file of class BillsPlotSystem
 */

#include "billsplotsystem.h"

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

Plotter * BillsPlotSystem::createPlotter(const QVector<QString> _fieldnames, const QVector<QDate> _dates, const QVector<QVector<int> > _values)
{
    return new BarPlotter(_fieldnames, _dates, _values);
}
