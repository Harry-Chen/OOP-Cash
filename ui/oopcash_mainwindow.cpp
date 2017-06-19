#include "oopcash_mainwindow.h"
#include "ui_oopcash_mainwindow.h"

OOPCash_MainWindow::OOPCash_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OOPCash_MainWindow)
{
    ui->setupUi(this);
    userman = new UserManager(DatabaseHelper::getDb());
    userMap = userman->getAllItems();
    pDetailWidget = nullptr;
    pRecordCostWidget = nullptr;
    pQueryWidget = nullptr;
    initWidgets();
}

OOPCash_MainWindow::~OOPCash_MainWindow()
{
    delete ui;
}

void OOPCash_MainWindow::initWidgets() {
    Isloggedin = false;
    delete pQueryWidget;
    delete pRecordCostWidget;
    delete pDetailWidget;
    pQueryWidget = nullptr;
    pRecordCostWidget = nullptr;
    pDetailWidget = nullptr;
    ui->setButton->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    ui->tabWidget->setCurrentIndex(tabIndex::home);
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
    ui->loginoutButton->setText(QObject::tr("登录"));
    ui->usernameLabel->setText(QObject::tr("好像还没有登录呢~"));
    initWidgets();         //clear data recieved...
}

void OOPCash_MainWindow::on_loginSuccess(ID idInfo) {
    Isloggedin = true;
    pQueryWidget = new QueryWidget(ui->queryTab);
    pQueryWidget->setUserman(userman);
    pRecordCostWidget = new RecordCostEarnWidget(ui->addTab);
    pRecordCostWidget->init(userman);
    pDetailWidget = new DetailWidget(ui->detailTab, userman);

    connect(this, SIGNAL(dataFreshSignal()), pRecordCostWidget, SLOT(refresh()));
    connect(this, SIGNAL(dataFreshSignal()), pDetailWidget, SLOT(consult()));

    ui->gridLayout_queryTab->addWidget(pQueryWidget);
    ui->gridLayout_addTab->addWidget(pRecordCostWidget);
    ui->gridLayout_detailTab->addWidget(pDetailWidget);

    ui->setButton->setEnabled(true);
    ui->tabWidget->setEnabled(true);

    u_id = idInfo;
    User theUser = userMap[u_id];
    ui->usernameLabel->setText(theUser.nickname.isEmpty() ? theUser.username : theUser.nickname);
    ui->loginoutButton->setText(QObject::tr("登出"));
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

void OOPCash_MainWindow::on_importButton_clicked()
{
    auto importor = new dataImporter(userman);
    if(importor->doImport()) {
        emit dataFreshSignal();
    }
}

void OOPCash_MainWindow::on_addButton_clicked() {
    ui->tabWidget->setCurrentIndex(tabIndex::add);
}

void OOPCash_MainWindow::on_queryButton_clicked() {
    ui->tabWidget->setCurrentIndex(tabIndex::query);
}

void OOPCash_MainWindow::on_detailButton_clicked() {
    ui->tabWidget->setCurrentIndex(tabIndex::detail);
}

void OOPCash_MainWindow::on_userconfigButton_clicked() {
    ui->setButton->click();
}
