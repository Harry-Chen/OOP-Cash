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
 * @file   plotter.h
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Header file of class Plotter
 */

#ifndef PLOTTER_H
#define PLOTTER_H

#include <qcustomplot.h>

/**
 * @brief The Plotter class, an abstract product, plot a chart using QCustomPlot(the builder)
 */
class Plotter : public QWidget
{

public:
    /**
     * @brief construct a Plotter by data
     * @param _fieldnames QVector of fieldnames, corresponding to graphs
     * @param _dates QVector of dates, which is the key (xAxis) in graph
     * @param _values Matrix of values, which is the value (yAxis) in graph
     */
    Plotter(const QVector<QString> _fieldnames, const QVector<QDate> _dates, const QVector< QVector<int> > _values)
        :fieldnames_(_fieldnames),
          dates_(_dates),
          values_(_values)
    {}
    /**
     * @brief plot the chart
     * @param custom_plot ptr to a QCustomPlot
     */
    virtual void plot(QCustomPlot * custom_plot) = 0;
    virtual ~Plotter(){}
protected:
    const QVector<QString> fieldnames_;
    const QVector<QDate> dates_;
    const QVector< QVector<int> > values_;
};

#endif // PLOTTER_H
