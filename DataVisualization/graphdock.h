#ifndef GRAPHDOCK_H
#define GRAPHDOCK_H

#include <QDockWidget>
#include "qcustomplot.h"
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
