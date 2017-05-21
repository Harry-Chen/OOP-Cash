#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include "util/constants.h"

namespace Ui {
class loginDlg;
}

class loginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit loginDlg(QWidget *parent = 0);
    ~loginDlg();

signals:
    void loginSuccessSignal(ID);

private slots:
    void on_loginButton_clicked();
    void on_switchButton_toggled(bool checked);

private:
    Ui::loginDlg *ui;
    ID u_id;
    bool switchButtonPressed;
    bool login();
    bool signin();
};

#endif // LOGINDLG_H
