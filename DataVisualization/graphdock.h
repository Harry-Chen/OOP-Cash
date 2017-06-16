#ifndef GRAPHDOCK_H
#define GRAPHDOCK_H

#include <QDockWidget>
#include "qcustomplot.h"
//#include "process/processor.h"
//#include "plot/processor/processor.h"
#include "plot/plotter/plotter.h"
//#include "process/balanceprocessor.h"

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

    void setupDemo1(QCustomPlot *customPlot);
    void setupDemo2(QCustomPlot *customPlot);
    void setupMyDemo(QCustomPlot *customPlot){pPlotter -> plot(customPlot);}
};

#endif // GRAPHDOCK_H
