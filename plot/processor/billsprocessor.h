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
 * @file   billsprocessor.h
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Header file of class BillsProcessor
 */

#ifndef BILLSPROCESSOR_H
#define BILLSPROCESSOR_H

#include "processor.h"

class BillsProcessor : public Processor
{
    ID (* GetFieldnameptr) (const Bill &);
    QDate (*GetDateptr) (const QDate &);
public:
    using Processor::Processor;
    void SetGetFieldname (ID (*func) (const Bill &)) {GetFieldnameptr = func;}
    void SetGetDate (QDate (*func) (const QDate &)) {GetDateptr = func;}
    ID GetFieldname(int i)
    {
        if (GetFieldnameptr)
        return (*GetFieldnameptr) (bills_[i]);
        else return -1; //error
    }
    QDate GetDate(int i)
    {
        if (GetDateptr)
        return(*GetDateptr) (bills_[i].date);
        else return QDate::currentDate(); //error
    }
};

#endif // BILLSPROCESSOR_H
