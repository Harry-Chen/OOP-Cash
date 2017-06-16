#ifndef BILLSPLOTTER_H
#define BILLSPLOTTER_H

#include "plot/plotter/plotter.h"

class BillsPlotter : public Plotter
{
public:
    //BillsPlotter();
    using Plotter::Plotter;

    void plot(QCustomPlot *custom_plot);
};

#endif // BILLSPLOTTER_H
