#include "graphdock.h"
#include "ui_graphdock.h"

GraphDock::GraphDock(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::GraphDock)
{
    ui->setupUi(this);
}

GraphDock::~GraphDock()
{
    delete ui;
}
