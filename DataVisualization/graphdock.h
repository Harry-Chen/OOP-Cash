#ifndef GRAPHDOCK_H
#define GRAPHDOCK_H

#include <QDockWidget>

namespace Ui {
class GraphDock;
}

class GraphDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit GraphDock(QWidget *parent = 0);
    ~GraphDock();

private:
    Ui::GraphDock *ui;
};

#endif // GRAPHDOCK_H
