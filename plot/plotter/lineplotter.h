#ifndef LINEPLOTTER_H
#define LINEPLOTTER_H

#include "plotter.h"

class LinePlotter : public Plotter
{
public:
    using Plotter::Plotter;
    void plot(QCustomPlot *custom_plot);
};

#endif // LINEPLOTTER_H
