#include "oopcash_mainwindow.h"
#include "ui_oopcash_mainwindow.h"

OOPCash_MainWindow::OOPCash_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OOPCash_MainWindow)
{
    ui->setupUi(this);
    userman = new UserManager(DatabaseHelper::getDb());
    userMap = userman->getAllItems();

    pQueryWidget = new QueryWidget(ui->statTab);
    pQueryWidget->setUserman(userman);

    init();

    pQueryWidget->show();
}

OOPCash_MainWindow::~OOPCash_MainWindow()
{
    delete ui;
}

void OOPCash_MainWindow::init() {
    Isloggedin = false;
    ui->setButton->setEnabled(false);
    ui->tabWidget->setEnabled(false);
//    if(userman != nullptr) {
//        delete userman;
//        userman = nullptr;
//    }
//    userman = new UserManager(DatabaseHelper::getDb());

    //other init...
}

void OOPCash_MainWindow::showloginDlg() {
    auto dlg = new loginDlg(userman, this);
    connect(dlg, SIGNAL(loginSuccessSignal(ID, QString)), this, SLOT(on_loginSuccess(ID, QString)));
    connect(dlg, SIGNAL(userMapUpdate()), this, SLOT(on_userMapUpdate));
    dlg->exec();
}

void OOPCash_MainWindow::showUserSetDlg() {
    auto dlg = new userSetDialog(u_id, userman, userMap, this);
    connect(dlg, SIGNAL(userMapUpdate()), this, SLOT(on_userMapUpdate));
    dlg->exec();
}

void OOPCash_MainWindow::logout() {
    userman->logout();
}

void OOPCash_MainWindow::on_loginSuccess(ID idInfo, QString nameInfo) {
    Isloggedin = true;
    ui->setButton->setEnabled(true);
    ui->tabWidget->setEnabled(true);
    u_id = idInfo;
    ui->usernameLabel->setText(nameInfo);
    ui->loginoutButton->setText("logout");
}

void OOPCash_MainWindow::on_userMapUpdate() {
    userMap = userman->getAllItems();
}

void OOPCash_MainWindow::on_loginoutButton_clicked()
{
    if(!Isloggedin) {
        showloginDlg();
        //userMap = userman->getAllItems();
    }
    else {
        logout();
        ui->loginoutButton->setText("login");
        ui->usernameLabel->setText("好像还没有登录呢~");
        init();         //clear data recieved...
    }
}

void OOPCash_MainWindow::on_setButton_clicked()
{
    showUserSetDlg();
}
