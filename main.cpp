#include <QApplication>
#include <QDebug>
#include <sqlpp11/sqlpp11.h>

#include "util/common.h"
#include "util/database_helper.h"
#include "dao/usermanager.h"
#include "dao/currencymanager.h"
#include "dao/accountmanager.h"
#include "dao/categorymanager.h"
#include "model/user.h"
#include "model/currency.h"
#include "model/account.h"
#include "model/category.h"

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

    UserManager *userman = new UserManager(DatabaseHelper::getDb());
    User newUser(-1, "Test", "Test Test", "1234");
    newUser.id = userman->addItem(newUser);
    userman->getAllItems();
    newUser = User(-1, "Test", "Test Test", "1234");
    newUser.id = userman->login(newUser);
    newUser.nickname = "Test Modified";
    newUser.username = "test";
    userman->modifyItem(newUser);
    userman->getAllItems();

    CurrencyManager *currman = new CurrencyManager(DatabaseHelper::getDb());
    Currency newCurrency(-1, "NTD", 487);
    newCurrency.id = currman->addItem(newCurrency);
    currman->getAllItems();
    newCurrency.name = "RMB";
    newCurrency.rate = 100;
    currman->modifyItem(newCurrency);
    currman->getAllItems();

    AccountManager *accman = new AccountManager(userman);
    Account newAccount(-1, "Wallet", newUser.id, newCurrency.id);
    newAccount.id = accman->addItem(newAccount);
    accman->getAllItems();
    newAccount.name = "Card";
    accman->modifyItem(newAccount);
    newAccount.uid = -1;
    accman->modifyItem(newAccount);
    accman->getAllItems();

    CategoryManager *catman = new CategoryManager(userman);
    Category newCat(-1, "Food", -1);
    newCat.id = catman->addItem(newCat);
    catman->getAllItems();
    newCat.name = "Drink";
    newCat.uid = newUser.id;
    catman->modifyItem(newCat);
    catman->getAllItems();

    catman->removeItemById(newCat.id);
    delete catman;
    catman = nullptr;
    accman->removeItemById(newAccount.id);
    delete accman;
    accman = nullptr;
    userman->removeItemById(newUser.id);
    delete userman;
    userman = nullptr;
    currman->removeItemById(newCurrency.id);
    delete currman;
    currman = nullptr;

    logging::trace("Application End===========");
    return 0;
}
