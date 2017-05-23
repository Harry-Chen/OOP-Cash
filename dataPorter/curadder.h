#ifndef CURADDER_H
#define CURADDER_H
#include "itemadder.h"
#include "dao/currencymanager.h"
#include "model/currency.h"

class curAdder : public itemAdder
{
    CurrencyManager * curman;
public:
    curAdder(QJsonObject &_obj, UserManager * _userman);
    bool add(QJsonObject & _item);
};

#endif // CURADDER_H
