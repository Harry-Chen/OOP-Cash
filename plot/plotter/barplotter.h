#ifndef BILLSPLOTTER_H
#define BILLSPLOTTER_H

#include "plot/plotter/plotter.h"

class BarPlotter : public Plotter
{
public:
    using Plotter::Plotter;
    void plot(QCustomPlot *custom_plot);
};

#endif // BILLSPLOTTER_H
