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
 * @file   graphdock.cpp
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Implementation file of class GraphDock
 */

#include "graphdock.h"
#include "ui_graphdock.h"

GraphDock::GraphDock (Plotter * _pPlotter, QWidget * parent):
    QDockWidget(parent),
    ui(new Ui::GraphDock),
    pPlotter(_pPlotter)
{
    ui->setupUi(this);
    setupMyDemo(ui->QCP);
    setWindowTitle(QObject::tr("绘图窗口"));
}

GraphDock::~GraphDock()
{
    delete ui;
    if(pPlotter) delete pPlotter;
}
