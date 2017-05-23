#ifndef ITEMADDER_H
#define ITEMADDER_H
#include "dao/usermanager.h"
#include <QString>
#include <QJsonObject>

class itemAdder
{
protected:
    QString key;
    QJsonObject obj;
    //ItemManager* man;
    UserManager* userman;

public:
    itemAdder(const QJsonObject & _obj, UserManager* _userman);
    bool additems();
    virtual bool add(QJsonObject & _item) = 0;
};

#endif // ITEMADDER_H
