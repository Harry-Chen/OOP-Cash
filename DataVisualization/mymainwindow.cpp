#include "mymainwindow.h"
#include "ui_mymainwindow.h"

MyMainWindow::MyMainWindow(QWidget *parent, UserManager * _pUserMan) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow),
    pUserman(_pUserMan)
{
    ui->setupUi(this);
    pQueryWidget = new QueryWidget(this);
    //GraphDockPtr = new GraphDock;
    pQueryWidget->setUserman(pUserman);
    pQueryWidget->show();
    //connect(ui->pushButton,SIGNAL(clicked(bool)),this, SLOT(showGraphDock()));
}

MyMainWindow::~MyMainWindow()
{
    delete ui;
}

//void MyMainWindow::showGraphDock()
//{
//    this->GraphDockPtr->show();
//    //this->GraphDockPtr->exec();
//}

void MyMainWindow::setUserman(UserManager * _pUserMan)
{
    //auto *newCategoryManager= new CategoryManager(_pUserMan);
    pUserman = _pUserMan;
}
