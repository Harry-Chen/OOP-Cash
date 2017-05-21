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

void OOPCash_MainWindow::showloginDlg() {
    auto dlg = new loginDlg(this);
    connect(dlg,SIGNAL(loginSuccessSignal(ID)),this,SLOT(on_loginSuccess(ID)));
    dlg->show();
    dlg->exec();
}

void OOPCash_MainWindow::on_loginSuccess(ID idInfo) {
    Isloggedin = true;
    u_id = idInfo;
}

void OOPCash_MainWindow::on_loginoutButton_clicked()
{
    if(!Isloggedin) {
        showloginDlg();
        if(Isloggedin) {
            ui->loginoutButton->setText("logout");
            ui->usernameLabel->setText( (p_user->nickname.isEmpty()) ? p_user->username : p_user->nickname );
        }
    }
    else {
        logout();
        ui->loginoutButton->setText("login");
        ui->usernameLabel->setText("好像还没有登录呢~");
        init();         //clear data recieved...
    }
}
