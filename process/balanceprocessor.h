#ifndef BALANCEPROCESSOR_H
#define BALANCEPROCESSOR_H
#include "process/processorbase.h"
#include <QVector>
#include <QMap>
#include <QList>
#include "model/bill.h"
#include "dao/query.h"
#include "dao/usermanager.h"
#include "util/database_helper.h"
#include "dao/accountmanager.h"

class BalanceProcessor :public ProcessorBase
{
    QList <ID> accountIds;
    ID getY(int i);
    ID userId;
public:
    BalanceProcessor(const QDate & dateFrom, const QDate & dateTo, UserManager * userman);
    bool processAll();
};

#endif // BALANCEPROCESSOR_H
