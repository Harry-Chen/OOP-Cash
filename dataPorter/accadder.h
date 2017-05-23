#ifndef ACCADDER_H
#define ACCADDER_H
#include "itemadder.h"
#include "dao/accountmanager.h"
#include "dao/currencymanager.h"
#include "model/account.h"


class accAdder : public itemAdder
{
    AccountManager * accman;
    CurrencyManager * curman;

public:
    accAdder(QJsonObject & _obj, UserManager* _userman);
    bool add(QJsonObject &_item);
};

#endif // ACCADDER_H
