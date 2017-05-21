﻿#include <QApplication>
#include <QDebug>
#include <QDate>
#include <QDateTime>
#include <sqlpp11/sqlpp11.h>

#include "util/common.h"
#include "util/database_helper.h"
#include "dao/usermanager.h"
#include "dao/currencymanager.h"
#include "dao/accountmanager.h"
#include "dao/categorymanager.h"
#include "dao/billmanager.h"
#include "dao/query.h"
#include "model/user.h"
#include "model/currency.h";
#include "model/account.h"
#include "model/category.h"
#include "model/bill.h"
#include "DataVisualization/mymainwindow.h"
#include "datavisualization/querywidget.h"

//#define nchDebug
//#include "graphmainwindow.h"
//#include "DataVisualization/guigetdata.h"
/*
int main(int argc, char *argv[])
{
    auto *userman = new UserManager(DatabaseHelper::getDb());
    User newUser(-1, "Test", "Test Test", "1234");
    newUser.id = userman->addItem(newUser);
    userman->getAllItems();
    newUser = User(-1, "Test", "Test Test", "1234");
    newUser.id = userman->login(newUser);
    newUser.nickname = "Test Modified";
    newUser.username = "test";
    userman->modifyItem(newUser);
    userman->getAllItems();

    QApplication windows(argc, argv);
    MyMainWindow *myMainWindow = new MyMainWindow;
    myMainWindow->show();

    return windows.exec();
}

*/



#ifndef nchDebug

namespace sql = sqlpp::sqlite3;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logging::Logger::instance().setLogDir(QCoreApplication::applicationDirPath().toStdString());
    logging::Logger::instance().setLogFilePrefix(APP_NAME.toStdString());
#ifdef _DEBUG
    logging::Logger::instance().setMinLevel(logging::l_trace);
#else
    logging::Logger::instance().setMinLevel(logging::l_info);
#endif


    logging::trace("Application Start===========");

    DatabaseHelper::initializeDatabase();

    auto *userman = new UserManager(DatabaseHelper::getDb());
    User newUser(-1, "Test", "Test Test", "1234");
    newUser.id = userman->addItem(newUser);
    newUser.id = userman->login(newUser);


    auto *currman = new CurrencyManager(userman);
    Currency newCurrency(-1, newUser.id,"NTD", 487);
    newCurrency.id = currman->addItem(newCurrency);

    auto *accman = new AccountManager(userman);
    Account newAccount(-1, "Wallet", newUser.id, newCurrency.id);
    newAccount.id = accman->addItem(newAccount);


    auto *catman = new CategoryManager(userman);
    Category newCat1(-1, "Food1", newUser.id);
    newCat1.id = catman->addItem(newCat1);
    Category newCat2(-1, "Food2", newUser.id);
    newCat2.id = catman->addItem(newCat2);
    Category newCat3(-1, "Food3", newUser.id);
    newCat3.id = catman->addItem(newCat3);
    Category newCat4(-1, "Food4", newUser.id);
    newCat4.id = catman->addItem(newCat4);
    Category newCat5(-1, "Food5", newUser.id);
    newCat5.id = catman->addItem(newCat5);
    Category newCat6(-1, "Food6", newUser.id);
    newCat6.id = catman->addItem(newCat6);
    Category newCat7(-1, "Food7", newUser.id);
    newCat7.id = catman->addItem(newCat7);



    auto *billman = new BillManager(userman);
    Bill newBill(-1, -1, newAccount.id, newUser.id, newCat1.id,
                 1000u, newCurrency.id, QDateTime::currentDateTime(), true, QDate(2017,5,1));
    newBill.id = billman->addItem(newBill);

    QApplication windows(argc, argv);
    MyMainWindow *myMainWindow = new MyMainWindow(0, userman);
   // myMainWindow->setUserman(userman);
    myMainWindow->show();

    return windows.exec();

    delete billman;
    billman = nullptr;
    delete catman;
    catman = nullptr;
    delete accman;
    accman = nullptr;
    userman->removeItemById(newUser.id);
    delete userman;
    userman = nullptr;
    delete currman;

    logging::trace("Application End===========");



    return 0;
}

#endif
