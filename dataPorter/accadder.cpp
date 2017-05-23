#include "accadder.h"

accAdder::accAdder(const QJsonObject & _obj, UserManager *_userman) : itemAdder(_obj, _userman) {
    key = "account";
    accman = new AccountManager(userman);
    curman = new CurrencyManager(userman);
}

bool accAdder::add(QJsonObject & _item) {
    if(!(_item.contains("name") && _item.contains("currency"))) {
        return false;
    }
    auto acc_item = Account(-1, _item.take("name").toString(), userman->getLoggedInUid(), curman->getIdByName( _item.take("currency").toString()));
    return (accman->addItem(acc_item) != -1);
}
