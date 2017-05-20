#ifndef OOPCASH_MAINWINDOW_H
#define OOPCASH_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class OOPCash_MainWindow;
}

class OOPCash_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OOPCash_MainWindow(QWidget *parent = 0);
    ~OOPCash_MainWindow();

private:
    Ui::OOPCash_MainWindow *ui;
};

#endif // OOPCASH_MAINWINDOW_H
