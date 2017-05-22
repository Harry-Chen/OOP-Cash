#ifndef BALANCEPROCESSOR_H
#define BALANCEPROCESSOR_H
#include "process/processorbase.h"
#include <QVector>
#include <QMap>
#include "model/bill.h"
#include "dao/query.h"
#include "dao/usermanager.h"
#include "util/database_helper.h"

class BalanceProcessor :public ProcessorBase
{

public:
    BalanceProcessor(const QDate & dateFrom, const QDate & dateTo, UserManager * userman);
    ID getY(int i);
    bool processAll();
};

#endif // BALANCEPROCESSOR_H
