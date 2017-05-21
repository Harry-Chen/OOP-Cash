#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include "graphdock.h"
#include "querywidget.h"

namespace Ui {
class MyMainWindow;
}

class MyMainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    //void showGraphDock();

public:
    explicit MyMainWindow(QWidget *parent, UserManager * _pUserMan);
    ~MyMainWindow();
    void setUserman(UserManager *);
private:
    Ui::MyMainWindow *ui;
    GraphDock * GraphDockPtr;
    UserManager * pUserman;
    QueryWidget * pQueryWidget;
};

#endif // MYMAINWINDOW_H
