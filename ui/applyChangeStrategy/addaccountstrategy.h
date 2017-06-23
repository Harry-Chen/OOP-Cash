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
  * @file addaccountstrategy.h
  * @author Zeping Niu <nnznk12@gmail.com>
  * @date 2017.5
  * @brief Header file for class AddAccountStrategy
  */


#ifndef ADDACCOUNTSTRATEGY_H
#define ADDACCOUNTSTRATEGY_H

#include "applychangestrategy.h"

/**
 * @brief The strategy to add Account
 */
class AddAccountStrategy : public ApplyChangeStrategy
{
public:
	/**
	 * @brief use the construction function of ApplyChangeStrategy
	 * @param w pointer of EditItemWidget
	 * @param userman pointer of userManager
	 */
	using ApplyChangeStrategy::ApplyChangeStrategy;
	/**
	 * @brief applyChange
	 * @return true if apply the modification successfully, else false
	 */
	virtual bool applyChange();
	/**
	 * @brief applyDelete
	 * @return true if delete successfully, else false
	 */
	virtual bool applyDelete();
};

#endif // ADDACCOUNTSTRATEGY_H
