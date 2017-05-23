#ifndef BILLADDER_H
#define BILLADDER_H
#include "itemadder.h"
#include "dao/accountmanager.h"
#include "dao/categorymanager.h"
#include "dao/currencymanager.h"
#include "dao/billmanager.h"
#include "model/bill.h"


class billAdder : public itemAdder
{
    AccountManager * accman;
    CategoryManager * catman;
    CurrencyManager * curman;
    BillManager * billman;

public:
    billAdder(const QJsonObject &_obj, UserManager* _userman);
    bool add(QJsonObject &_item);
};

#endif // BILLADDER_H
