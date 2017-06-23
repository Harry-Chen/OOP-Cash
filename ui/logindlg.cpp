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
 * @file   logindlg.cpp
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class LoginDlg
 */

#include <QMessageBox>

#include "model/user.h"
#include "dao/usermanager.h"
#include "logindlg.h"
#include "ui_logindlg.h"

LoginDlg::LoginDlg(UserManager *usermanInfo, QWidget *parent) :
    userman(usermanInfo),
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);

    ui->nicknameEdit->hide();
    ui->nicknameLabel->hide();
    ui->pwAgainEdit->hide();
    ui->pwAgainLabel->hide();
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->pwAgainEdit->setEchoMode(QLineEdit::Password);

    switchButtonPressed = false;
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

bool LoginDlg::login() {
    auto newuser = new User(-1, ui->usernameEdit->text(), QString(), ui->passwordEdit->text());
    u_id = userman->login(*newuser);
    return ( (u_id == -1) ? false : true );
}

bool LoginDlg::signup() {
    if(ui->usernameEdit->text().isEmpty()) {
        QMessageBox::warning(this, QObject::tr("注册失败"), QObject::tr("用户名不能为空"));
        return false;
    }
    if(ui->passwordEdit->text().isEmpty()) {
        QMessageBox::warning(this, QObject::tr("注册失败"), QObject::tr("密码不能为空"));
        return false;
    }
    if(ui->passwordEdit->text() != ui->pwAgainEdit->text()) {
        QMessageBox::warning(this, QObject::tr("注册失败"), QObject::tr("两次输入的密码不一致"));
        return false;
    }
    User newuser(-1, ui->usernameEdit->text(), ui->nicknameEdit->text(), ui->passwordEdit->text());
    u_id = userman->addItem(newuser);
    return ( (u_id == -1) ? false : true );
}

void LoginDlg::on_loginButton_clicked()
{
    //sign in...
    if(switchButtonPressed) {
        if(signup()) {
            QMessageBox::information(this, QObject::tr("注册成功"), \
                                     QObject::tr("请牢记您的用户名和密码.\n") \
                                     + ui->usernameEdit->text() + QObject::tr("，欢迎使用 Expensé！"));
            ui->switchButton->click();
        }
        else {
            QMessageBox::warning(this, QObject::tr("注册失败"), QObject::tr("用户名已被使用"));
        }
        return;
    }

    //log in...
    if(login()) {
        emit loginSuccessSignal(u_id);
        this->close();
    }
    else {
        QMessageBox::warning(this, QObject::tr("登录失败"), QObject::tr("用户名或密码错误"));
    }
}


void LoginDlg::on_switchButton_clicked()
{
    switchButtonPressed = !switchButtonPressed;
    ui->usernameEdit->clear();
    ui->nicknameEdit->clear();
    ui->passwordEdit->clear();
    ui->pwAgainEdit->clear();
    this->setWindowTitle((switchButtonPressed ? QObject::tr("注册") : QObject::tr("登录")));
    ui->loginButton->setText((switchButtonPressed ? QObject::tr("注册") : QObject::tr("登录")));
    ui->switchButton->setText(switchButtonPressed ? QObject::tr("登录") : QObject::tr("注册"));
    ui->nicknameEdit->setVisible(switchButtonPressed);
    ui->nicknameLabel->setVisible(switchButtonPressed);
    ui->pwAgainLabel->setVisible(switchButtonPressed);
    ui->pwAgainEdit->setVisible(switchButtonPressed);
}
