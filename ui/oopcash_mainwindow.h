#ifndef OOPCASH_MAINWINDOW_H
#define OOPCASH_MAINWINDOW_H

#include <QMainWindow>
#include "util/constants.h"
#include "model/user.h"

namespace Ui {
class OOPCash_MainWindow;
}

class OOPCash_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OOPCash_MainWindow(QWidget *parent = 0);
    ~OOPCash_MainWindow();
    bool Isloggedin;
    ID u_id;
    User * p_user;

private slots:
    void on_loginoutButton_clicked();

private:
    Ui::OOPCash_MainWindow *ui;
    void init();

    bool login();   //get u_id, p_user and return whether successed.
    void logout();

};

#endif // OOPCASH_MAINWINDOW_H
