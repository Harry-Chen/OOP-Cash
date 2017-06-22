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
 * @file   billsprocessor.cpp
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Implementation file of class BillsProcessor
 */


#include "billsprocessor.h"

ID BillsProcessor::GetFieldname(int i)
{
    if (GetFieldnameptr)
    return (*GetFieldnameptr) (bills_[i]);
    else return -1; //error
}

QDate BillsProcessor::GetDate(int i)
{
    if (GetDateptr)
    return(*GetDateptr) (bills_[i].date);
    else return QDate::currentDate(); //error
}
