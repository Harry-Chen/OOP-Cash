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
 * @file   lineplotter.cpp
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Implementation file of class LinePLotter
 */

#include "lineplotter.h"

void LinePlotter::plot(QCustomPlot *custom_plot)
{
    QVector<double> time_double;
    QVector<QVector<double> > value_double;
    QVector<double> temp;
    for(int j = 0; j < dates_.size(); j++)
        temp.push_back((double)values_[0][j]/100);
      value_double.push_back(temp);
      temp.clear();

    for(int i = 0; i < dates_.size(); ++i)
        time_double.push_back( (double)QDateTime(dates_[i]).toTime_t());

    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    custom_plot->setBackground(QBrush(gradient));

    custom_plot->addGraph();
    QColor color(20+300/4.0,70*(1.6-1/4.0), 150, 250);
    custom_plot->graph()->setLineStyle(QCPGraph::lsLine);
    custom_plot->graph()->setPen(QPen(color.lighter(200)));
    custom_plot->graph()->setData(time_double, value_double[0]);

    // make left and bottom axes always transfer their ranges to right and top axes:
    QAbstractAnimation::connect(custom_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), custom_plot->xAxis2, SLOT(setRange(QCPRange)));
    QAbstractAnimation::connect(custom_plot->yAxis, SIGNAL(rangeChanged(QCPRange)), custom_plot->yAxis2, SLOT(setRange(QCPRange)));

    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("yyyy\nMMMM. d");
    custom_plot->xAxis->setTicker(dateTicker);
    custom_plot->xAxis->setBasePen(QPen(Qt::white));
    custom_plot->xAxis->setTickPen(QPen(Qt::white));
    custom_plot->xAxis->grid()->setVisible(true);
    custom_plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    custom_plot->xAxis->setTickLabelColor(Qt::white);
    custom_plot->xAxis->setLabelColor(Qt::white);
    custom_plot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
    custom_plot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    custom_plot->yAxis->setBasePen(QPen(Qt::white));
    custom_plot->yAxis->setTickPen(QPen(Qt::white));
    custom_plot->yAxis->setSubTickPen(QPen(Qt::white));
    custom_plot->yAxis->grid()->setSubGridVisible(true);
    custom_plot->yAxis->setTickLabelColor(Qt::white);
    custom_plot->yAxis->setLabelColor(Qt::white);
    custom_plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    custom_plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // set axis labels:
    custom_plot->xAxis->setLabel(QObject::tr("日期"));
    custom_plot->yAxis->setLabel(QObject::tr("余额"));

    // set axis ranges to show all data:
    custom_plot->graph()->rescaleAxes();

    custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}
