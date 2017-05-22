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
    ui->nicknameEdit->setText(userMap[u_id].nickname);
}

userSetDialog::~userSetDialog()
{
    delete ui;
}

bool userSetDialog::freshUserInfo() {
    User newUser = userMap[u_id];
    newUser.nickname = ui->nicknameEdit->text();
    newUser.setPassword(ui->passwordEdit->text());
    return userman->modifyItem(newUser);
}

void userSetDialog::on_freshButton_clicked() {
    if(ui->nicknameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "更新失败", "昵称不可以为空哦");
        return;
    }
    if(ui->passwordEdit->text() != ui->pwAgainEdit->text()) {
        QMessageBox::warning(this, "Failed", "Two passwords are not the same.");
        return;
    }
    if(ui->passwordEdit->text().isEmpty()) {
        QMessageBox::warning(this, "更新失败", "空密码是不可以的哟");
        return;
    }
    if(freshUserInfo()) {
        emit userMapUpdate();
        QMessageBox::information(this, "更新成功", "获得新昵称：" + ui->nicknameEdit->text() + "\n要牢记密码哦~");
        this->close();
    }
    else {
        QMessageBox::critical(this, "更新失败", "发生了不可名状的错误>.<");
    }
}
