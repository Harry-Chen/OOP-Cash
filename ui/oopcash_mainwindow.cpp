/**
 * Copyright 2017 OOP-Cash Team

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   oopcash_mainwindow.cpp
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class OOPCash_MainWindow
 */

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
    auto dlg = new LoginDlg(userman, this);
    connect(dlg, SIGNAL(loginSuccessSignal(ID)), this, SLOT(on_loginSuccess(ID)));
    connect(dlg, SIGNAL(userMapUpdate()), this, SLOT(on_userMapUpdate()));
    dlg->exec();
}

void OOPCash_MainWindow::showUserSetDlg() {
    auto dlg = new UserSetDlg(u_id, userman, userMap, this);
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
    auto exportor = new DataExporter(userman);
    exportor->doExport();
}

void OOPCash_MainWindow::on_importButton_clicked()
{
    auto importor = new DataImporter(userman);
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

void OOPCash_MainWindow::on_tabWidget_currentChanged(int index)
{
	if(index == tabIndex::add) {
		pRecordCostWidget->refresh();
	}
}
