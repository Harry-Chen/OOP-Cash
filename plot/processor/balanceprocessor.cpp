#include "balanceprocessor.h"

bool BalanceProcessor::ProcessAll()
{
    for(int i = 0; i < bills_.size(); ++i)
    {
        if(bills_[i].to == -1) bills_[i].quantity = -bills_[i].quantity;
        else if(bills_[i].from == -1) ;
        else bills_[i].quantity = 0;
    }
    Processor::ProcessAll();
    for(int i = 0; i < matrix_.size(); ++i)
        for(int j = 0; j < dates_.size(); ++j)
            if(j)matrix_[i][j] += matrix_[i][j-1];
    return true;
}

ID BalanceProcessor::GetFieldname(int i)
{
    return bills_[i].creator;
}
