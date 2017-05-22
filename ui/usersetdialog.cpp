#include "usersetdialog.h"
#include "ui_usersetdialog.h"
#include <QMessageBox>

userSetDialog::userSetDialog(ID userInfo, UserManager *usermanInfo, QMap<ID, User> &userMapInfo, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userSetDialog),
    u_id(userInfo),
    userman(usermanInfo),
    userMap(userMapInfo)
{
    ui->setupUi(this);
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->pwAgainEdit->setEchoMode(QLineEdit::Password);
}

userSetDialog::~userSetDialog()
{
    delete ui;
}

bool userSetDialog::setNickname() {
    User newUser = userMap[u_id];
    newUser.nickname = ui->nicknameEdit->text();
    return userman->modifyItem(newUser);
}

bool userSetDialog::setPassword() {
    User newUser = userMap[u_id];
    newUser.setPassword(ui->passwordEdit->text());
    return userman->modifyItem(newUser);
}

void userSetDialog::on_nicknameSetButton_clicked()
{
    if(ui->nicknameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "更新昵称失败", "昵称不可以为空哦");
        return;
    }
    if(setNickname()) {
        userMap = userman->getAllItems();
        QMessageBox::information(this, "更新昵称成功", "获得新昵称：" + ui->nicknameEdit->text());
    }
    else {
        QMessageBox::critical(this, "更新昵称失败", "发生了不可名状的错误>.<");
    }
}

void userSetDialog::on_passwordSetButton_clicked()
{
    if(ui->passwordEdit->text() != ui->pwAgainEdit->text()) {
        QMessageBox::warning(this, "Sign failed", "Two passwords are not the same.");
        return;
    }
    if(setPassword()) {
        userMap = userman->getAllItems();
        QMessageBox::information(this, "更改密码成功", "要牢记哦~" + ui->nicknameEdit->text());
    }
    else {
        QMessageBox::critical(this, "更改密码失败", "发生了不可名状的错误>.<");
    }
}
