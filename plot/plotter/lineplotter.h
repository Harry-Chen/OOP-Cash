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
 * @file   lineplotter.h
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Header file of class LinePlotter
 */

#ifndef LINEPLOTTER_H
#define LINEPLOTTER_H

#include "plotter.h"

/**
 * @brief The LinePlotter class, a concrete product, plot a linechart
 * @details The class is written under the guidance of sample file in QCustomPlot
 */
class LinePlotter : public Plotter
{
public:
    using Plotter::Plotter;
    /**
     * @brief overload plot in Plotter
     * @param custom_plot a ptr to a QCustomPlot
     */
    void plot(QCustomPlot *custom_plot);
};

#endif // LINEPLOTTER_H
