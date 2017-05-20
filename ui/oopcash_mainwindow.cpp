#include "oopcash_mainwindow.h"
#include "ui_oopcash_mainwindow.h"

OOPCash_MainWindow::OOPCash_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OOPCash_MainWindow)
{
    ui->setupUi(this);
}

OOPCash_MainWindow::~OOPCash_MainWindow()
{
    delete ui;
}
