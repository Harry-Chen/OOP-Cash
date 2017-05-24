#ifndef TABLEDOCK_H
#define TABLEDOCK_H

#include <QDockWidget>
#include <QTableView>
#include "process/processor.h"
#include "process/balanceprocessor.h"

namespace Ui {
class TableDock;
}

class TableDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit TableDock(ProcessorBase *_pProcessor,QWidget *parent = 0);
    ~TableDock();
private:
    Ui::TableDock *ui;
    ProcessorBase * pProcessor;

    void setupTable(QTableView *table);
};

#endif // TABLEDOCK_H
