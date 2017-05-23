#include "oopcash_mainwindow.h"
#include "ui_oopcash_mainwindow.h"

OOPCash_MainWindow::OOPCash_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OOPCash_MainWindow)
{
    ui->setupUi(this);
    userman = new UserManager(DatabaseHelper::getDb());
    userMap = userman->getAllItems();

    pQueryWidget = new QueryWidget(ui->QueryWidget);
    pQueryWidget->setUserman(userman);
    pRecardCostWidget = new RecordCostWidget(ui->addTab);
    pRecardCostWidget->init(userman);

    init();

    pQueryWidget->show();
    pDetailWidget = new DetailWidget(ui->detailTab, userman);
    pDetailWidget->show();
    pRecardCostWidget->show();
}

OOPCash_MainWindow::~OOPCash_MainWindow()
{
    delete ui;
}

void OOPCash_MainWindow::init() {
    Isloggedin = false;
    ui->setButton->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    ui->tabWidget->setCurrentIndex(0);
//    if(userman != nullptr) {
//        delete userman;
//        userman = nullptr;
//    }
//    userman = new UserManager(DatabaseHelper::getDb());

    //other init...
}

void OOPCash_MainWindow::showloginDlg() {
    auto dlg = new loginDlg(userman, this);
    connect(dlg, SIGNAL(loginSuccessSignal(ID)), this, SLOT(on_loginSuccess(ID)));
    connect(dlg, SIGNAL(userMapUpdate()), this, SLOT(on_userMapUpdate()));
    dlg->exec();
}

void OOPCash_MainWindow::showUserSetDlg() {
    auto dlg = new userSetDialog(u_id, userman, userMap, this);
    connect(dlg, SIGNAL(userMapUpdate()), this, SLOT(on_userMapUpdate()));
    dlg->exec();
}

void OOPCash_MainWindow::logout() {
    userman->logout();
    ui->loginoutButton->setText("login");
    ui->usernameLabel->setText("好像还没有登录呢~");
    init();         //clear data recieved...
}

void OOPCash_MainWindow::on_loginSuccess(ID idInfo) {
    Isloggedin = true;
    ui->setButton->setEnabled(true);
    ui->tabWidget->setEnabled(true);

    u_id = idInfo;
    User theUser = userMap[u_id];
    ui->usernameLabel->setText(theUser.nickname.isEmpty() ? theUser.username : theUser.nickname);
    ui->loginoutButton->setText("logout");
}

void OOPCash_MainWindow::on_userMapUpdate() {
    userMap = userman->getAllItems();
    User theUser = userMap[u_id];
    ui->usernameLabel->setText(theUser.nickname.isEmpty() ? theUser.username : theUser.nickname);
}

void OOPCash_MainWindow::on_loginoutButton_clicked()
{
    Isloggedin ? logout() : showloginDlg();
}

void OOPCash_MainWindow::on_setButton_clicked()
{
    showUserSetDlg();
}

void OOPCash_MainWindow::on_exportButton_clicked()
{
    auto exportor = new dataExporter(userman);
    exportor->doExport();
}
