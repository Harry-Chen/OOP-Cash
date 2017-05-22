#include "balanceprocessor.h"

BalanceProcessor::BalanceProcessor(const QDate & dateFrom, const QDate & dateTo, UserManager * userman)
{
      raw =  Query::newQuery(DatabaseHelper::getDb()).addCreatorId(userman->getLoggedInUid())
                .setDateRange(dateFrom,dateTo).doQuery();
      nameMap.insert(userman->getLoggedInUid(), userman->getAllItems()[userman->getLoggedInUid()].nickname);
}

bool BalanceProcessor::processAll()
{
    ProcessorBase::processAll();
    for(int i = 0; i < matrix.size(); ++i)
        for(int j = 0; j < X.size(); ++j)
            if(j)matrix[i][j] += matrix[i][j-1];
    return true;
}

ID BalanceProcessor::getY(int i)
{
    return raw[i].creator;
}
