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

//产品系列2的基类
#ifndef PLOTTER_H
#define PLOTTER_H

#include <qcustomplot.h>

class Plotter : public QWidget
{

public:
    Plotter(const QVector<QString> _fieldnames, const QVector<QDate> _dates, const QVector< QVector<int> > _values)
        :fieldnames_(_fieldnames),
          dates_(_dates),
          values_(_values)
    {}
    virtual void plot(QCustomPlot * custom_plot) = 0;
    virtual ~Plotter(){}
protected:
    const QVector<QString> fieldnames_;
    const QVector<QDate> dates_;
    const QVector< QVector<int> > values_;
};

#endif // PLOTTER_H
