#include "oopcash_mainwindow.h"
#include "ui_oopcash_mainwindow.h"

OOPCash_MainWindow::OOPCash_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OOPCash_MainWindow)
{
    ui->setupUi(this);
    userman = nullptr;
    DatabaseHelper::initializeDatabase(); //do once? do when logout?
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
    connect(dlg,SIGNAL(loginSuccessSignal()),this,SLOT(on_loginSuccess()));
    dlg->exec();
}

void OOPCash_MainWindow::logout() {
    userman->logout();
}

void OOPCash_MainWindow::on_loginSuccess() {
    Isloggedin = true;
//    u_id = idInfo;
}

void OOPCash_MainWindow::on_loginoutButton_clicked()
{
    if(!Isloggedin) {
        showloginDlg();
        if(Isloggedin) {
            ui->loginoutButton->setText("logout");
            //这里需要更新界面：设置用户名
            //ui->usernameLabel->setText( (p_user->nickname.isEmpty()) ? p_user->username : p_user->nickname );
        }
    }
    else {
        logout();
        ui->loginoutButton->setText("login");
        ui->usernameLabel->setText("好像还没有登录呢~");
        init();         //clear data recieved...
    }
}
