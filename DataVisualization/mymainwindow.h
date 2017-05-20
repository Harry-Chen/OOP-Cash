#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>
#include "graphdock.h"

namespace Ui {
class MyMainWindow;
}

class MyMainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void showGraphDock();

public:
    explicit MyMainWindow(QWidget *parent = 0);
    ~MyMainWindow();

private:
    Ui::MyMainWindow *ui;
    GraphDock * GraphDockPtr;
};

#endif // MYMAINWINDOW_H
