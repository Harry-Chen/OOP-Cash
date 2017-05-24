#include "curadder.h"

curAdder::curAdder(QJsonObject & _obj, UserManager *_userman) : itemAdder(_obj, _userman) {
    key = "currency";
    curman = new CurrencyManager(userman);
}

bool curAdder::add(QJsonObject _item) {
    if(!(_item.contains("name")
         && _item.contains("rate")
      )) {
        return false;
    }
    auto cur_item = Currency(-1, userman->getLoggedInUid(), _item.take("name").toString(), _item.take("rate").toInt(0100));
    return (curman->addItem(cur_item) != -1);
}


