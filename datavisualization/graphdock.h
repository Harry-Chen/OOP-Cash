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
 * @file   graphdock.h
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Header file of class GraphDock
 */

#ifndef GRAPHDOCK_H
#define GRAPHDOCK_H

#include <QDockWidget>
#include <qcustomplot.h>

#include "plot/plotter/plotter.h"

namespace Ui {
class GraphDock;
}

/**
 * @brief The GraphDock class, generate a dock to show the chart
 */
class GraphDock : public QDockWidget
{
    Q_OBJECT

public:
    /**
     * @brief construct a GraphDock and init is with ptr to a plotter and ptr to its parent
     * @param _pPlotter ptr to a plotter
     * @param parent the parent of this dock (which is 0)
     */
    explicit GraphDock(Plotter * _pPlotter,QWidget *parent = 0);
    /**
      * @brief destruct the GraphDock, delete pPlotter if it's not null
      */
    ~GraphDock();

private:
    Ui::GraphDock *ui;
    Plotter * pPlotter;
    /**
     * @brief setup the plotter to plot, delegates the opperations to plotter
     * @param ptr to QCustomPlot
     */
    void setupMyDemo(QCustomPlot *customPlot){pPlotter -> plot(customPlot);}
};

#endif // GRAPHDOCK_H
