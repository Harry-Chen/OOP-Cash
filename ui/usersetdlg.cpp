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
 * @file   usersetdlg.cpp
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class UserSetDlg
 */

#include <QMessageBox>

#include "usersetdlg.h"
#include "ui_usersetdialog.h"

UserSetDlg::UserSetDlg(ID userInfo, UserManager *usermanInfo, QMap<ID, User> &userMapInfo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserSetDialog),
    u_id(userInfo),
    userman(usermanInfo),
    userMap(userMapInfo)
{
    ui->setupUi(this);
    this->setWindowTitle(QObject::tr("更新资料"));
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->pwAgainEdit->setEchoMode(QLineEdit::Password);
    ui->nicknameEdit->setText(userMap[u_id].nickname);
}

UserSetDlg::~UserSetDlg()
{
    delete ui;
}

bool UserSetDlg::freshUserInfo() {
    User newUser = userMap[u_id];
    newUser.nickname = ui->nicknameEdit->text();
    newUser.setPassword(ui->passwordEdit->text());
    return userman->modifyItem(newUser);
}

void UserSetDlg::on_freshButton_clicked() {
    if(ui->nicknameEdit->text().isEmpty()) {
        QMessageBox::warning(this, QObject::tr("更新失败"), QObject::tr("昵称不可以为空哦"));
        return;
    }
    if(ui->passwordEdit->text() != ui->pwAgainEdit->text()) {
        QMessageBox::warning(this, QObject::tr("更新失败"), QObject::tr("两次密码不一致"));
        return;
    }
    if(ui->passwordEdit->text().isEmpty()) {
        QMessageBox::warning(this, QObject::tr("更新失败"), QObject::tr("空密码是不可以的哟"));
        return;
    }
    if(freshUserInfo()) {
        emit userMapUpdate();
        QMessageBox::information(this, QObject::tr("更新成功"), QObject::tr("获得新昵称：") + ui->nicknameEdit->text() + QObject::tr("\n要牢记密码哦~"));
        this->close();
    }
    else {
        QMessageBox::critical(this, QObject::tr("更新失败"), QObject::tr("发生了不可名状的错误>.<"));
    }
}
