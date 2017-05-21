#ifndef OOPCASH_MAINWINDOW_H
#define OOPCASH_MAINWINDOW_H

#include <QMainWindow>
#include "util/constants.h"
#include "model/user.h"

#include "ui/logindlg.h"

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
    //User * p_user;

public slots:
    void on_loginSuccess(ID);

private slots:
    void on_loginoutButton_clicked();

private:
    Ui::OOPCash_MainWindow *ui;
    void init();

    void showloginDlg();   //get u_id
    void logout();

};

#endif // OOPCASH_MAINWINDOW_H
