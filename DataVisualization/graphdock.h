#ifndef GRAPHDOCK_H
#define GRAPHDOCK_H

#include <QDockWidget>
#include "include/qcustomplot.h"
#include "process/processor.h"

namespace Ui {
class GraphDock;
}

class GraphDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit GraphDock(QWidget *parent = 0);
    ~GraphDock();

private:
    Ui::GraphDock *ui;
    Processor * pProcessor;

    void setupDemo1(QCustomPlot *customPlot);
    void setupDemo2(QCustomPlot *customPlot);
    void setupMyDemo(QCustomPlot *customPlot);
};

#endif // GRAPHDOCK_H
