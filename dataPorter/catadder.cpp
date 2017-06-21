#include "catadder.h"

catAdder::catAdder(QJsonObject &_obj, UserManager *_userman): itemAdder(_obj, _userman) {
    key = "category";
    catman = new CategoryManager(userman);
}

bool catAdder::add(QJsonObject _item) {
    if(!(_item.contains("name"))) {
        return false;
    }
    auto cat_item = Category(-1,_item.take("name").toString(), userman->getLoggedInUid());
    return (catman->addItem(cat_item) != -1);
}
