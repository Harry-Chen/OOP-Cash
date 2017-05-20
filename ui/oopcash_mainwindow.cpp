#include "oopcash_mainwindow.h"
#include "ui_oopcash_mainwindow.h"
#include "model/user.h"

OOPCash_MainWindow::OOPCash_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OOPCash_MainWindow)
{
    ui->setupUi(this);
}

OOPCash_MainWindow::~OOPCash_MainWindow()
{
    delete ui;
}

void OOPCash_MainWindow::on_loginoutButton_clicked()
{
    if(!Isloggedin) {
        if(login()) {
            ui->loginoutButton->setText("logout");
            ui->usernameLabel->setText( (p_user->nickname.isEmpty()) ? p_user->username : p_user->nickname );
        }
    }
    else {
        logout();
        ui->loginoutButton->setText("login");
        init();         //clear data recieved...
    }
}
