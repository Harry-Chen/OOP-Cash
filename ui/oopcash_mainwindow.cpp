#include "oopcash_mainwindow.h"
#include "ui_oopcash_mainwindow.h"

OOPCash_MainWindow::OOPCash_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OOPCash_MainWindow)
{
    ui->setupUi(this);
    userman = nullptr;
    init();
}

OOPCash_MainWindow::~OOPCash_MainWindow()
{
    delete ui;
}

void OOPCash_MainWindow::init() {
    Isloggedin = false;
    if(userman != nullptr) {
        delete userman;
        userman = nullptr;
    }
    userman = new UserManager(DatabaseHelper::getDb());
    //other init...
}

void OOPCash_MainWindow::showloginDlg() {
    auto dlg = new loginDlg(userman, this);
    QObject::connect(dlg, SIGNAL(loginSuccessSignal(ID, QString)), this, SLOT(on_loginSuccess(ID, QString)));
    dlg->exec();
}

void OOPCash_MainWindow::logout() {
    userman->logout();
}

void OOPCash_MainWindow::on_loginSuccess(ID idInfo, QString nameInfo) {
    Isloggedin = true;
    u_id = idInfo;
    ui->usernameLabel->setText(nameInfo);
    ui->loginoutButton->setText("logout");
}

void OOPCash_MainWindow::on_loginoutButton_clicked()
{
    if(!Isloggedin) {
        showloginDlg();
    }
    else {
        logout();
        ui->loginoutButton->setText("login");
        ui->usernameLabel->setText("好像还没有登录呢~");
        init();         //clear data recieved...
    }
}
