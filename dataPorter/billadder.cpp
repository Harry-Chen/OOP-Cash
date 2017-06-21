#include "billadder.h"
#include <QDate>
#include <QDateTime>

billAdder::billAdder(QJsonObject & _obj, UserManager *_userman) : itemAdder(_obj, _userman) {
    key = "bills";
    accman = new AccountManager(userman);
    catman = new CategoryManager(userman);
    curman = new CurrencyManager(userman);
    billman = new BillManager(userman);
}

bool billAdder::add(QJsonObject _item) {
    if(!(   _item.contains("accFrom")
            && _item.contains("accTo")
            && _item.contains("catName")
            && _item.contains("curName")
            && _item.contains("quantity")
            && _item.contains("finished")
            && _item.contains("date")
            && _item.contains("note"))) {
        return false;
    }
    auto bill_item = Bill(
                -1,
                accman->getIdByName(_item.take("accFrom").toString()),
                accman->getIdByName(_item.take("accTo").toString()),
                userman->getLoggedInUid(),
                catman->getIdByName(_item.take("catName").toString()),
                _item.take("quantity").toInt(),
                curman->getIdByName(_item.take("curName").toString()),
                QDateTime::currentDateTime(),
                _item.take("finished").toBool(),
                QDate::fromString(_item.take("date").toString(), "yyyy-MM-dd"),
                _item.take("note").toString()
                );
    return ( billman->addItem(bill_item) != -1);
}


