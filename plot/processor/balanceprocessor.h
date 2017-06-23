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
 * @file   balanceprocessor.h
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Header file of class BalanceProcessor
 */

#ifndef BALANCEPROCESSOR_H
#define BALANCEPROCESSOR_H

#include "processor.h"

/**
 * @brief The BalanceProcessor class, a derived class of Processor(concrete product), process bills for linechart
 */
class BalanceProcessor : public Processor
{
    /**
     * @brief overload GetFieldname in Processor, get the nickname of User
     * @param i No.i
     * @return ID of the User
     */
    ID GetFieldname(int i);
public:
    using Processor::Processor;
    /**
     * @brief overload ProcessAll in Processor, add some operation before and after Processor::ProcessAll()
     * @return if process successfully, return true
     */
    bool ProcessAll();
};

#endif // BALANCEPROCESSOR_H
