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
