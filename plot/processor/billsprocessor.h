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

/**
 * @brief The BillsProcessor class, a derived class of Processor(concrete product), process bills for barchart
 */
class BillsProcessor : public Processor
{
    ///< a ptr to the func to get fieldname
    ID (* GetFieldnameptr) (const Bill &);
    ///< a ptr to the func to get date
    QDate (*GetDateptr) (const QDate &);
public:
    using Processor::Processor;
    /**
     * @brief get the method to get filedname(as a func ptr)
     */
    void SetGetFieldname (ID (*func) (const Bill &)) {GetFieldnameptr = func;}
    /**
     * @brief get the method to get date(as a func ptr)
     */
    void SetGetDate (QDate (*func) (const QDate &)) {GetDateptr = func;}
    /**
     * @brief overload GetFieldname in Processor, get fieldname using the func ptr
     * @param i No.i
     * @return ID of fieldname of No.i bill
     */
    ID GetFieldname(int i);
    /**
     * @brief overload GetDate
     * @param i No.i
     * @return processed date of No.i bill
     */
    QDate GetDate(int i);

};

#endif // BILLSPROCESSOR_H
