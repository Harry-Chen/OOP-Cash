#ifndef DATAEXPORTER_H
#define DATAEXPORTER_H
#include "dao/usermanager.h"
#include "dao/accountmanager.h"
#include "dao/billmanager.h"
#include "dao/categorymanager.h"
#include "dao/currencymanager.h"
#include "dao/query.h"
#include "model/user.h"
#include "model/account.h"
#include "model/bill.h"
#include "model/category.h"
#include "model/currency.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class dataExporter {
private:
    UserManager * userman;
    AccountManager * accman;
    CategoryManager * catman;
    CurrencyManager * curman;
    QMap<ID, User> userMap;
    QMap<ID, Account> accMap;
    QMap<ID, Category> catMap;
    QMap<ID, Currency> curMap;
    QVector<Bill> exportBills;
    QJsonArray getBillArray(QVector<Bill>&);
    QJsonArray getCurrencyArray();
    QJsonArray getAccountArray();

public:
    dataExporter(UserManager * _userman);
    bool doExport();
};

#endif // DATAEXPORTER_H
