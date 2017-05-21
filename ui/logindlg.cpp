#include <QMessageBox>
#include "logindlg.h"
#include "ui_logindlg.h"
#include "model/user.h"
#include "dao/usermanager.h"

loginDlg::loginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDlg)
{
    ui->setupUi(this);
    ui->pwAgainEdit->setVisible(false);
    ui->pwAgainEdit->setVisible(false);
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->pwAgainEdit->setEchoMode(QLineEdit::Password);
}

loginDlg::~loginDlg()
{
    delete ui;
}

bool loginDlg::login() {
    auto newuser = new User(-1, ui->usernameEdit->text(),QString(), ui->passwordEdit->text());
    auto userman = new UserManager;
    u_id = userman->login(*newuser);
    return ( (u_id == -1) ? false : true );
}

bool loginDlg::signin() {
    if(ui->passwordEdit->text() != ui->pwAgainEdit->text()) {
        QMessageBox::warning(this, "注册失败", "两次密码输入不一致", QMessageBox::Ok, QMessageBox::Ok);
        return false;
    }
    auto newuser = new User(-1, ui->usernameEdit->text(),QString(), ui->passwordEdit->text());
    auto userman = new UserManager;
    u_id = userman->addItem(*newuser);
    return ( (u_id == -1) ? false : true );
}

void loginDlg::on_loginButton_clicked()
{
    if(switchButtonPressed) {
        if(signin()) {
            ui->switchButton->toggle();
        }
        return;
    }
    if(login()) {
        emit loginSuccess(u_id);
        this->close();
    }
    else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误", QMessageBox::Ok, QMessageBox::Ok);
    }
}

void loginDlg::on_switchButton_toggled(bool checked)
{
    switchButtonPressed = checked;
}
