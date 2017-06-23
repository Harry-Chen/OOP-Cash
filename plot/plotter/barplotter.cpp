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
 * @file   barplotter.cpp
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Implementation file of class BarPlotter
 */

#include "barplotter.h"

void BarPlotter::plot(QCustomPlot *custom_plot)
{
    QVector<QVector<double> > value_double;
    QVector<double> temp;
    for(int i = 0; i < fieldnames_.size(); i++)
    {
        for(int j = 0; j < dates_.size(); j++)
            temp.push_back((double)values_[i][j]/100);
        value_double.push_back(temp);
        temp.clear();
     }

    QVector<double> ticks;
    QVector<QString> labels;
    for(int i = 0; i < dates_.size(); ++i)
    {
        ticks << (double)i;
        labels << dates_[i].toString();
    }

    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    custom_plot->setBackground(QBrush(gradient));

    // create empty bar chart objects:
    QVector <QCPBars *> bars;
    for (int gi=0; gi < fieldnames_.size(); ++gi)
    {
        QCPBars * bar =new QCPBars(custom_plot->xAxis, custom_plot->yAxis);
        bar->setAntialiased(false);
        bar->setStackingGap(1);

        bar->setName(fieldnames_[gi]);
        bar->setPen(QPen(QColor((111 + 200 * gi) % 256, (9 + 200 * gi) % 256, (176 + 200 * gi) % 256).lighter(170)));
        bar->setBrush(QColor((111 + 200 * gi) % 256, (9 + 200 * gi) % 256, (176 + 200 * gi) % 256).lighter(170));
        if(gi) bar->moveAbove(bars[gi - 1]);
        bar->setData(ticks, value_double[gi]);
        bars.push_back(bar);
    }

    // prepare x axis with country labels:
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    custom_plot->xAxis->setTicker(textTicker);
    custom_plot->xAxis->setTickLabelRotation(60);
    custom_plot->xAxis->setSubTicks(false);
    custom_plot->xAxis->setTickLength(0, 4);
    custom_plot->xAxis->setRange(0, 20);
    custom_plot->xAxis->setBasePen(QPen(Qt::white));
    custom_plot->xAxis->setTickPen(QPen(Qt::white));
    custom_plot->xAxis->grid()->setVisible(true);
    custom_plot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    custom_plot->xAxis->setTickLabelColor(Qt::white);
    custom_plot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    custom_plot->yAxis->setRange(0, 1000);
    custom_plot->yAxis->rescale();
    custom_plot->yAxis->setPadding(5); // a bit more space to the left border
    custom_plot->yAxis->setLabel(QObject::tr("总值"));
    custom_plot->yAxis->setBasePen(QPen(Qt::white));
    custom_plot->yAxis->setTickPen(QPen(Qt::white));
    custom_plot->yAxis->setSubTickPen(QPen(Qt::white));
    custom_plot->yAxis->grid()->setSubGridVisible(true);
    custom_plot->yAxis->setTickLabelColor(Qt::white);
    custom_plot->yAxis->setLabelColor(Qt::white);
    custom_plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    custom_plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    //custom_plot->graph()->rescaleAxes();

    // setup legend:
    custom_plot->legend->setVisible(true);
    custom_plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    custom_plot->legend->setBrush(QColor(255, 255, 255, 100));
    custom_plot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    custom_plot->legend->setFont(legendFont);
    custom_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

}
