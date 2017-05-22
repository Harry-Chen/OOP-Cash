#include <QApplication>
#include <QDebug>
#include <QDate>
#include <QDateTime>
#include <sqlpp11/sqlpp11.h>

#include "util/database_helper.h"
#include "dao/usermanager.h"
#include "dao/currencymanager.h"
#include "dao/accountmanager.h"
#include "dao/categorymanager.h"
#include "dao/billmanager.h"
#include "dao/query.h"
#include "model/user.h"
#include "model/currency.h"
#include "model/account.h"
#include "model/category.h"
#include "model/bill.h"
#include "DataVisualization/mymainwindow.h"
#include "datavisualization/querywidget.h"
#include "ui/oopcash_mainwindow.h"
#include "ui/recordcostwidget.h"

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
	
    auto w = new OOPCash_MainWindow;
    w->show();

    auto userman = new UserManager(DatabaseHelper::getDb());
    auto myMainWindow = new MyMainWindow(0, userman);
    myMainWindow->show();

    return a.exec();
	
//	RecordCostWidget* ww = new RecordCostWidget();
//	ww->init(userman);
//	ww->show();

    // auto *userman = new UserManager(DatabaseHelper::getDb());
    // User newUser(-1, "Test", "Test Test", "1234");
    // newUser.id = userman->addItem(newUser);
    // newUser.id = userman->login(newUser);


    // auto *currman = new CurrencyManager(userman);
    // Currency newCurrency(-1, newUser.id,"NTD", 487);
    // newCurrency.id = currman->addItem(newCurrency);

    // auto *accman = new AccountManager(userman);
    // Account newAccount(-1, "Wallet", newUser.id, newCurrency.id);
    // newAccount.id = accman->addItem(newAccount);


    // auto *catman = new CategoryManager(userman);
    // Category newCat1(-1, "Food1", newUser.id);
    // newCat1.id = catman->addItem(newCat1);
    // Category newCat2(-1, "Food2", newUser.id);
    // newCat2.id = catman->addItem(newCat2);
    // Category newCat3(-1, "Food3", newUser.id);
    // newCat3.id = catman->addItem(newCat3);
    // Category newCat4(-1, "Food4", newUser.id);
    // newCat4.id = catman->addItem(newCat4);
    // Category newCat5(-1, "Food5", newUser.id);
    // newCat5.id = catman->addItem(newCat5);
    // Category newCat6(-1, "Food6", newUser.id);
    // newCat6.id = catman->addItem(newCat6);
    // Category newCat7(-1, "Food7", newUser.id);
    // newCat7.id = catman->addItem(newCat7);



    // auto *billman = new BillManager(userman);
    // Bill newBill1(-1, -1, newAccount.id, newUser.id, newCat1.id,
                 // 1000u, newCurrency.id, QDateTime::currentDateTime(), true, QDate(2017,5,1));
    // newBill1.id = billman->addItem(newBill1);
    // Bill newBill2(-1, -1, newAccount.id, newUser.id, newCat2.id,
                 // 1001u, newCurrency.id, QDateTime::currentDateTime(), true, QDate(2017,5,1));
    // newBill2.id = billman->addItem(newBill2);
    // std:: cout << billman->getAllItems().size() << std::endl;



//    auto *userman = new UserManager(DatabaseHelper::getDb());
//    User newUser(-1, "Test", "Test Test", "1234");
//    newUser.id = userman->addItem(newUser);
//    userman->getAllItems();
//    newUser = User(-1, "Test", "Test Test", "1234");
//    newUser.id = userman->login(newUser);
//    newUser.nickname = "Test Modified";
//    newUser.username = "test";
//    userman->modifyItem(newUser);
//    userman->getAllItems();

//    auto *currman = new CurrencyManager(userman);
//    Currency newCurrency(-1, newUser.id,"NTD", 487);
//    newCurrency.id = currman->addItem(newCurrency);
//    currman->getAllItems();
//    newCurrency.name = "RMB";
//    newCurrency.rate = 100;
//    currman->modifyItem(newCurrency);
//    currman->getAllItems();

//    auto *accman = new AccountManager(userman);
//    Account newAccount(-1, "Wallet", newUser.id, newCurrency.id);
//    newAccount.id = accman->addItem(newAccount);
//    accman->getAllItems();
//    newAccount.name = "Card";
//    accman->modifyItem(newAccount);
//    newAccount.uid = -1;
//    accman->modifyItem(newAccount);
//    accman->getAllItems();

//    auto *catman = new CategoryManager(userman);
//    Category newCat(-1, "Food", newUser.id);
//    newCat.id = catman->addItem(newCat);
//    catman->getAllItems();
//    newCat.name = "Drink";
//    newCat.uid = newUser.id;
//    catman->modifyItem(newCat);
//    catman->getAllItems();

//    auto *billman = new BillManager(userman);
//    Bill newBill(-1, -1, newAccount.id, newUser.id, newCat.id,
//                 1000u, newCurrency.id, QDateTime::currentDateTime(), true, QDate(2017,5,1));
//    newBill.id = billman->addItem(newBill);
//    billman->getAllItems();
//    newBill.from = newAccount.id;
//    newBill.quantity = 2000;
//    newBill.note = "Hello World";
//    billman->modifyItem(newBill);
//    billman->getAllItems();

//    auto result = Query::newQuery(DatabaseHelper::getDb())
//            .addCreatorId(42)
//            .addCreatorId(newUser.id)
//            .addCategoryId(newCat.id)
//            .addFromAccountId(newAccount.id)
//            .setDateRange(QDate(2017,1,1), QDate(2017,12,31))
//            .setKeyword("Hello")
//            .doQuery();

//    delete billman;
//    billman = nullptr;
//    delete catman;
//    catman = nullptr;
//    delete accman;
//    accman = nullptr;
//    userman->removeItemById(newUser.id);
//    delete userman;
//    userman = nullptr;
//    delete currman;

//    logging::trace("Application End===========");
//    return 0;
}

