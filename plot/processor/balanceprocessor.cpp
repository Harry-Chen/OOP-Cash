/**
 * Copyright 2017 OOP-Cash Team

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   balanceprocessor.cpp
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Implementation file of class BalanceProcessor
 */

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
