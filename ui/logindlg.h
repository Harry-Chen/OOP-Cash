#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include "util/constants.h"
#include "dao/usermanager.h"

namespace Ui {
class loginDlg;
}

class loginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit loginDlg(UserManager *usermanInfo, QWidget *parent = 0);
    ~loginDlg();

signals:
    void loginSuccessSignal();

private slots:
    void on_loginButton_clicked();
    void on_switchButton_clicked();

private:
    Ui::loginDlg *ui;
    ID u_id;
    bool switchButtonPressed;
    bool login();
    bool signin();
    UserManager * userman;
};

#endif // LOGINDLG_H
