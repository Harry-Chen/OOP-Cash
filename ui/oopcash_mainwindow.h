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
 * @file   oopcash_mainwindow.h
 * @author Ice Coffee <ice438971718@gmail.com>
 * @date   2017.05
 * @brief  Header file of class OOPCash_MainWindow
 */

#ifndef OOPCASH_MAINWINDOW_H
#define OOPCASH_MAINWINDOW_H

#include <QMainWindow>
#include "util/database_helper.h"
#include "dao/usermanager.h"
#include "model/user.h"
#include "datavisualization/querywidget.h"
#include "ui/detailwidget.h"
#include "ui/recordcostearnwidget.h"
#include "ui/logindlg.h"
#include "ui/usersetdlg.h"
#include "dataPorter/dataexporter.h"
#include "dataPorter/dataimporter.h"

enum tabIndex{home=0, add, detail, query, port};

namespace Ui {
class OOPCash_MainWindow;
}

/**
 * @brief The OOPCash_MainWindow class
 */
class OOPCash_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OOPCash_MainWindow(QWidget *parent = 0);
    ~OOPCash_MainWindow();

signals:
    /**
     * @brief dataFreshSignal emit when data imported
     */
    void dataFreshSignal();

public slots:
    void on_loginSuccess(ID);
    void on_userMapUpdate();

private slots:
    void on_loginoutButton_clicked();
    void on_setButton_clicked();
    void on_exportButton_clicked();
    void on_importButton_clicked();
    void on_addButton_clicked();
    void on_queryButton_clicked();
    void on_detailButton_clicked();
    void on_userconfigButton_clicked();

private:
    Ui::OOPCash_MainWindow *ui;
    UserManager * userman;
    QMap<ID,User> userMap;

    bool Isloggedin;
    ID u_id;
    //Tab Pages
    DetailWidget * pDetailWidget;
    QueryWidget * pQueryWidget;
    RecordCostEarnWidget * pRecordCostWidget;
    void initWidgets();
    void showloginDlg();
    void showUserSetDlg();
    void logout();
};

#endif // OOPCASH_MAINWINDOW_H
