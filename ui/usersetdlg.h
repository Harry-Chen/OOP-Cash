/**
 * Copyright 2017 OOP-Cash Team

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   usersetdlg.h
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Header file of class UserSetDlg
 */

#ifndef USERSETDIALOG_H
#define USERSETDIALOG_H

#include <QDialog>
#include "dao/usermanager.h"
#include "model/user.h"

namespace Ui {
class UserSetDialog;
}

/**
 * @brief the dialog of user settings
 */
class UserSetDlg : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Initiate with ID, UserManager*, QMap<ID,User>&
     * @param userInfo user's ID
     * @param usermanInfo pointer to UserManager who called this dialog
     * @param userMapInfo reference to the userMap which contain the information of users
     */
    explicit UserSetDlg(ID userInfo, UserManager * usermanInfo, QMap<ID,User> &userMapInfo, QWidget *parent = 0);
    ~UserSetDlg();

signals:
    /**
     * @brief userMapUpdate emit when the UserMap need to update
     */
    void userMapUpdate();

private slots:
    void on_freshButton_clicked();

private:
    Ui::UserSetDialog *ui;
    ID u_id;
    UserManager * userman;
    QMap<ID,User> & userMap;
    /**
     * @brief freshUserInfo modify the user's information
     * @return succeeded or not
     */
    bool freshUserInfo();
};

#endif // USERSETDIALOG_H
