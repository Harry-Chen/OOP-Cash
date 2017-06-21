#include "balanceprocessor.h"

BalanceProcessor::BalanceProcessor(const QDate & dateFrom, const QDate & dateTo, UserManager * userman)
{
     //userId = userman->getLoggedInUid();
     //accountIds = AccountManager(userman).getAllItems().keys();
     raw =  Query::newQuery(DatabaseHelper::getDb()).addCreatorId(userman->getLoggedInUid())
                .setDateRange(dateFrom,dateTo).doQuery();
      nameMap.insert(userman->getLoggedInUid(), userman->getAllItems()[userman->getLoggedInUid()].nickname);
}

bool BalanceProcessor::processAll()
{
    for(int i = 0; i < raw.size(); ++i)
    {
        if(raw[i].to == -1) raw[i].quantity = -raw[i].quantity;
        else if(raw[i].from == -1) ;
        else raw[i].quantity = 0;
//        int indexFrom = accountIds.indexOf(userId);
//        int indexTo = accountIds.indexOf(userId);
//        if (indexFrom != -1 && indexTo != -1)
//            raw[i].quantity = 0;
//        else if (indexFrom != -1 && indexTo == -1)
//            raw[i].quantity = -raw[i].quantity;
//        else if (indexFrom == -1 && indexTo != -1);
//        else
//        {
//            logging::error("An abnormal bill!\n");
//        }
    }
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
