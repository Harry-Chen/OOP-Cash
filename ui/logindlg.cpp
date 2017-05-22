#include <QMessageBox>
#include "logindlg.h"
#include "ui_logindlg.h"
#include "model/user.h"
#include "dao/usermanager.h"

loginDlg::loginDlg(UserManager *usermanInfo, QWidget *parent) :
    userman(usermanInfo),
    QDialog(parent),
    ui(new Ui::loginDlg)
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

loginDlg::~loginDlg()
{
    delete ui;
}

bool loginDlg::login() {
    auto newuser = new User(-1, ui->usernameEdit->text(), QString(), ui->passwordEdit->text());
    u_id = userman->login(*newuser);
    return ( (u_id == -1) ? false : true );
}

bool loginDlg::signin() {
    if(ui->passwordEdit->text() != ui->pwAgainEdit->text()) {
        QMessageBox::warning(this, "Sign failed", "Two passwords are not the same.");
        return false;
    }
    User newuser(-1, ui->usernameEdit->text(), ui->nicknameEdit->text(), ui->passwordEdit->text());
    u_id = userman->addItem(newuser);
    return ( (u_id == -1) ? false : true );
}

void loginDlg::on_loginButton_clicked()
{
    //sign in...
    if(switchButtonPressed) {
        if(signin()) {
            QMessageBox::information(this, "注册成功", \
                                     "You've signed in successfully!\nPlease remember your username and password.\n" \
                                     + ui->usernameEdit->text() + ", welcome to OOP-Cash!");
            ui->switchButton->click();
        }
        else {
            QMessageBox::warning(this, "注册失败", "The username has been used.");
        }
        return;
    }

    //log in...
    if(login()) {
        emit loginSuccessSignal(u_id);
        this->close();
    }
    else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误");
    }
}

void loginDlg::on_switchButton_clicked()
{
    switchButtonPressed = !switchButtonPressed;
    ui->usernameEdit->clear();
    ui->nicknameEdit->clear();
    ui->passwordEdit->clear();
    ui->pwAgainEdit->clear();
    ui->loginButton->setText((switchButtonPressed ? "signin" : "login"));
    ui->switchButton->setText(switchButtonPressed ? "登录" : "注册");
    ui->nicknameEdit->setVisible(switchButtonPressed);
    ui->nicknameLabel->setVisible(switchButtonPressed);
    ui->pwAgainLabel->setVisible(switchButtonPressed);
    ui->pwAgainEdit->setVisible(switchButtonPressed);
}
