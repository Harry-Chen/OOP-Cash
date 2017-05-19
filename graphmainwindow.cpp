#include "graphmainwindow.h"
#include "ui_mainwindow.h"
#include "util/database_helper.h"

GraphMainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    startDate(QDateTime::currentDateTime()),
    endDate (startDate),
    query(query.newQuery(DatabaseHelper::getDb())),
    ui(new Ui::GraphMainWindow)
{
    ui->setupUi(this);
    //connect(ui->timeFrom, SIGNAL(dateChanged(QDate)), this, SLOT(getDate(QDate)));
    //connect(ui->timeTo, SIGNAL(dateChanged(QDate)), this, SLOT(getDate(QDate));
    //connects
}

GraphMainWindow::~MainWindow()
{
    delete ui;
}

void GraphMainWindow::on_timeFrom_dateChanged(const QDate &date)
{
    startDate = date;
}

void GraphMainWindow::on_timeTo_dateChanged(const QDate &date)
{
    endDate = date;
}

void GraphMainWindow::on_unfinished_stateChanged(int arg1)
{
    _finished = arg1;
}

void GraphMainWindow::on_Do_clicked()
{

}
