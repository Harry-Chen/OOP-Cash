#ifndef USERSETDIALOG_H
#define USERSETDIALOG_H

#include <QDialog>
#include "util/constants.h"
#include "dao/usermanager.h"
#include "model/user.h"

namespace Ui {
class userSetDialog;
}

class userSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit userSetDialog(ID userInfo, UserManager * usermanInfo, QMap<ID,User> &userMapInfo, QWidget *parent = 0);
    ~userSetDialog();

private slots:
    void on_nicknameSetButton_clicked();

    void on_passwordSetButton_clicked();

private:
    Ui::userSetDialog *ui;
    ID u_id;
    UserManager * userman;
    QMap<ID,User> & userMap;
    bool setNickname();
    bool setPassword();
};

#endif // USERSETDIALOG_H
