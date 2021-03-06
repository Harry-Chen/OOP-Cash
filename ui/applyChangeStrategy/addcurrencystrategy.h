﻿/**
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
  * @file addcurrencystrategy.h
  * @author Zeping Niu <nnznk12@gmail.com>
  * @date 2017.5
  * @brief Header file for class AddCurrencyStrategy
  */


#ifndef ADDCURRENCYSTRATEGY_H
#define ADDCURRENCYSTRATEGY_H

#include "applychangestrategy.h"

/**
 * @brief The strategy to add Currency
 */
class AddCurrencyStrategy : public ApplyChangeStrategy
{
public:
	/**
	 * @brief initiate with ItemEditWidget* and UserManager*
	 * @param w pointer of ItemEditWidget
	 * @param userman pointer of UserManager
	 */
	using ApplyChangeStrategy::ApplyChangeStrategy;
	/**
	 * @brief applyChange
	 * @return true if apply the modification successfully, else false
	 */
	virtual bool applyChange();
	/**
	 * @brief applyChange
	 * @return true if apply the modification successfully, else false
	 */
	virtual bool applyDelete();
};

#endif // ADDCURRENCYSTRATEGY_H
