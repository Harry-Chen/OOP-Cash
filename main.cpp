#include <QApplication>
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
#include "model/currency.h"
#include "model/account.h"
#include "model/category.h"
#include "model/bill.h"
#include "ui/oopcash_mainwindow.h"

#include "ui/recordcostwidget.h"

namespace sql = sqlpp::sqlite3;

int main(int argc, char *argv[])
{
    logging::Logger::instance().setLogDir(QCoreApplication::applicationDirPath().toStdString());
    logging::Logger::instance().setLogFilePrefix(APP_NAME.toStdString());
#ifdef _DEBUG
    logging::Logger::instance().setMinLevel(logging::l_trace);
#else
    logging::Logger::instance().setMinLevel(logging::l_info);
#endif
    QApplication a(argc, argv);
    DatabaseHelper::initializeDatabase();
	OOPCash_MainWindow * w = new OOPCash_MainWindow;
//	RecordCostWidget* ww = new RecordCostWidget();
//	ww->init(userman);
//	ww->show();
//    w->show();
//    return a.exec();

	logging::trace("Application Start===========");

	DatabaseHelper::initializeDatabase();

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

	auto *currman = new CurrencyManager(userman);
	Currency newCurrency(-1, newUser.id,"NTD", 487);
	newCurrency.id = currman->addItem(newCurrency);
	currman->getAllItems();
	newCurrency.name = "RMB";
	newCurrency.rate = 100;
	currman->modifyItem(newCurrency);
	currman->getAllItems();

	auto *accman = new AccountManager(userman);
	Account newAccount(-1, "Wallet", newUser.id, newCurrency.id);
	newAccount.id = accman->addItem(newAccount);
	accman->getAllItems();
	newAccount.name = "Card";
	accman->modifyItem(newAccount);
	newAccount.uid = -1;
	accman->modifyItem(newAccount);
	accman->getAllItems();

	auto *catman = new CategoryManager(userman);
	Category newCat(-1, "Food", newUser.id);
	newCat.id = catman->addItem(newCat);
	catman->getAllItems();
	newCat.name = "Drink";
	newCat.uid = newUser.id;
	catman->modifyItem(newCat);
	catman->getAllItems();

	auto *billman = new BillManager(userman);
	Bill newBill(-1, -1, newAccount.id, newUser.id, newCat.id,
				 1000u, newCurrency.id, QDateTime::currentDateTime(), true, QDate(2017,5,1));
	newBill.id = billman->addItem(newBill);
	billman->getAllItems();
	newBill.from = newAccount.id;
	newBill.quantity = 2000;
	newBill.note = "Hello World";
	billman->modifyItem(newBill);
	billman->getAllItems();

	auto result = Query::newQuery(DatabaseHelper::getDb())
			.addCreatorId(42)
			.addCreatorId(newUser.id)
			.addCategoryId(newCat.id)
			.addFromAccountId(newAccount.id)
			.setDateRange(QDate(2017,1,1), QDate(2017,12,31))
			.setKeyword("Hello")
			.doQuery();

	delete billman;
	billman = nullptr;
	delete catman;
	catman = nullptr;
	delete accman;
	accman = nullptr;
	//userman->removeItemById(newUser.id);
	//delete userman;
	//userman = nullptr;
	delete currman;

	logging::trace("Application End===========");
//    return 0;
	RecordCostWidget* ww = new RecordCostWidget();
	ww->init(userman);
	ww->show();
	w->show();
	return a.exec();
}
