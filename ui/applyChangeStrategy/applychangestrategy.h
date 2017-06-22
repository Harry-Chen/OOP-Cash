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
  * @file applychangestrategy.h
  * @author Zeping Niu <nnznk12@gmail.com>
  * @date 2017.5
  * @brief Header file for class ApplyChangeStrategy
  */


#ifndef APPLYCHANGESTRATEGY_H
#define APPLYCHANGESTRATEGY_H

#include "ui/edititemwidget.h"
#include "dao/usermanager.h"

/**
 * @brief Abstract class ApplyChangeStrategy
 */
class ApplyChangeStrategy
{
public:
	/**
	 * @brief ApplyChangeStrategy
	 * @param w the pointer of EditemWidget
	 * @param userman the pointer of UserManager
	 */
	ApplyChangeStrategy(EditItemWidget* w, UserManager* userman);
	/**
	 * @brief applyChange
	 * @return true if apply the modification successfully, else false
	 */
	virtual bool applyChange() = 0;
	/**
	 * @brief applyDelete
	 * @return true if delete successfully, else false
	 */
	virtual bool applyDelete() = 0;
protected:
	EditItemWidget* _w;
	UserManager* _userman;
};

#endif // APPLYCHANGESTRATEGY_H
