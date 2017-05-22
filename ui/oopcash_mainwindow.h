#ifndef OOPCASH_MAINWINDOW_H
#define OOPCASH_MAINWINDOW_H

#include <QMainWindow>
#include "util/database_helper.h"
#include "dao/usermanager.h"
#include "model/user.h"

#include "datavisualization/querywidget.h"
#include "ui/logindlg.h"
#include "ui/usersetdialog.h"

namespace Ui {
class OOPCash_MainWindow;
}

class OOPCash_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OOPCash_MainWindow(QWidget *parent = 0);
    ~OOPCash_MainWindow();

public slots:
    void on_loginSuccess(ID);
    void on_userMapUpdate();

private slots:
    void on_loginoutButton_clicked();
    void on_setButton_clicked();

private:
    Ui::OOPCash_MainWindow *ui;
    UserManager * userman;
    QMap<ID,User> userMap;
    QueryWidget * pQueryWidget;
    bool Isloggedin;
    ID u_id;
    void init();

    void showloginDlg();
    void showUserSetDlg();
    void logout();

};

#endif // OOPCASH_MAINWINDOW_H
