#ifndef DATAIMPORTER_H
#define DATAIMPORTER_H
#include "dao/usermanager.h"
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "accadder.h"
#include "curadder.h"
#include "billadder.h"

class dataImporter {
private:
    UserManager * userman;
    QJsonObject obj;
    itemAdder ** adder;

public:
    dataImporter(UserManager * _userman);
    bool doImport();
};

#endif // DATAIMPORTER_H
