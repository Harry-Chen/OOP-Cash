#include "tabledock.h"
#include "ui_tabledock.h"

TableDock::TableDock(ProcessorBase *_pProcessor,QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::TableDock),
    pProcessor(_pProcessor)
{
    ui->setupUi(this);
}

TableDock::~TableDock()
{
    delete ui;
}
