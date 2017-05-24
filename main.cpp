#include <QApplication>
#include <sqlpp11/sqlpp11.h>

#include "ui/oopcash_mainwindow.h"

namespace sql = sqlpp::sqlite3;

//#define GENERATE_DATA

#ifndef GENERATE_DATA


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
	
    auto w = new OOPCash_MainWindow();
    w->show();

    return a.exec();
}

#endif

#ifdef GENERATE_DATA

#include "util/common.h"
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
    User newUser(15, "Test", "Test Test", "1234");
    //newUser.id = userman->addItem(newUser);
    userman->login(newUser);
    //userman->modifyItem(newUser);

   // auto *currman = new CurrencyManager(userman);
     //   Currency newCurrency(-1, newUser.id,"NTD", 487);
      //  newCurrency.id = currman->addItem(newCurrency);

    //auto *accman = new AccountManager(userman);
       // accman->addItem(Account(-1, "Card 4", newUser.id, newCurrency.id));
        //accman->addItem(Account(25, "Card 1", newUser.id, newCurrency.id));
        //accman->addItem(Account(26, "Card 2", newUser.id, newCurrency.id));
        //accman->addItem(Account(27, "Card 3", newUser.id, newCurrency.id));

//    auto *catman = new CategoryManager(userman);

//        catman->addItem(Category(-1, "Breadfast", 15));
//        catman->addItem(Category(-1, "Lunch", 15));
//        catman->addItem(Category(-1, "Dinner", 15));
//        catman->addItem(Category(-1, "氪金", 15));

    auto *billman = new BillManager(userman);
    srand(8);
    int rAccountId1, rAccountId2, rCatId, rQuantity;
    bool rBool;
    QDate Date(2016,1,1);
    QDateTime DateTime(Date);

//    std::cout << DateTime.toString().toStdString() << std::endl;
//    DateTime.addDays(1);

//    std::cout << DateTime.addDays((qint64)1).toString().toStdString() << std::endl;

    for(qint64 i = 191; Date.addDays(i) <= QDate::currentDate(); ++i)
    {
        std::cout << i << std::endl;
        rAccountId1 = rand() % 3 + 23;
        rAccountId2 = rand() % 3 + 23;

        while(rAccountId2 == rAccountId1) rAccountId2 = rand() % 3 + 23;

        rCatId = rand() % 3 + 24;
        rQuantity = rand() % 10000;
        rBool = (bool)(rand() % 2);
       billman->addItem(Bill(-1, -1, rAccountId1, 15, rCatId,
                             rQuantity, -1, DateTime.addDays(i), rBool,Date.addDays(i)));
        rCatId = rand() % 3 + 24;
       rQuantity = rand() % 10000;
       rBool = (bool)(rand() % 2);
       billman->addItem(Bill(-1, rAccountId2, rAccountId1, 15, rCatId,
                             rQuantity, -1, DateTime.addDays(i), rBool,Date.addDays(i)));
        rCatId = rand() % 3 + 24;
       rQuantity = rand() % 10000;
       rBool = (bool)(rand() % 2);
       billman->addItem(Bill(-1, rAccountId2, -1, 15, rCatId,
                             rQuantity, -1, DateTime.addDays(i), rBool,Date.addDays(i)));
    }


    return 0;
}
#endif
