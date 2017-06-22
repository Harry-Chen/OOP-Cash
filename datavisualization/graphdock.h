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

class GraphDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit GraphDock(Plotter * ,QWidget *parent = 0);
    ~GraphDock();

private:
    Ui::GraphDock *ui;
    Plotter * pPlotter;
    void setupMyDemo(QCustomPlot *customPlot){pPlotter -> plot(customPlot);}
};

#endif // GRAPHDOCK_H
