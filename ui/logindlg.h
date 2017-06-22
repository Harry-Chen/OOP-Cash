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
 * @file   logindlg.h
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Header file of class LoginDlg
 */

#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>

#include "dao/usermanager.h"

namespace Ui {
class LoginDlg;
}

/**
 * @brief the dialog to log in.
 */
class LoginDlg : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Initiate with UserManager*
     * @param usermanInfo the pointer to the UserManager that called LoginDlg
     */
    explicit LoginDlg(UserManager *usermanInfo, QWidget *parent = 0);
    ~LoginDlg();

signals:
    /**
     * @brief loginSuccessSignal emit when succeed to log in
     */
    void loginSuccessSignal(ID);
    /**
     * @brief userMapUpdate emit when the UserMap need to update
     */
    void userMapUpdate();

private slots:
    void on_loginButton_clicked();
    void on_switchButton_clicked();

private:
    Ui::LoginDlg *ui;
    ID u_id;
    UserManager * userman;
    /**
     * @brief switchButtonPressed whether the SignUp/LogIn switchButtun is pressed
     */
    bool switchButtonPressed;
    /**
     * @brief login
     * @return succeeded or not
     */
    bool login();
    /**
     * @brief signup
     * @return succeeded or not
     */
    bool signup();
};

#endif // LOGINDLG_H
