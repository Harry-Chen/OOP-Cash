#include "mymainwindow.h"
#include "ui_mymainwindow.h"

MyMainWindow::MyMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow)
{
    ui->setupUi(this);
    GraphDockPtr = new GraphDock;
    connect(ui->pushButton,SIGNAL(clicked(bool)),this, SLOT(showGraphDock()));
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

void MyMainWindow::showGraphDock()
{
    this->GraphDockPtr->show();
    //this->GraphDockPtr->exec();
}
