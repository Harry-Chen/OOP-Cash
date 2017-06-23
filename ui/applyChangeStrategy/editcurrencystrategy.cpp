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
 * @file   editcurrencystrategy.cpp
 * @author Zeping Niu <nnznk12@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class EditCurrencyStrategy
 */


#include "editcurrencystrategy.h"

bool EditCurrencyStrategy::applyChange()
{
	QString oldName = _w->getLabelText(0); ///< old name of currency
	QString newName = _w->getLineEditText1(); ///< new name of currency
	double newRate = _w->getLineEditText2().toDouble(); ///< new rate of currency
	auto currman = new CurrencyManager(_userman);
	Currency curr = ItemSearcher::instance()->getItemByName(currman, oldName);
	curr.name = newName;
	curr.rate = newRate;
	bool success = currman->modifyItem(curr);
	delete currman;
	return success;
}

bool EditCurrencyStrategy::applyDelete()
{
	QString name = _w->getLabelText(0);
	auto currman = new CurrencyManager(_userman);
	Currency curr = ItemSearcher::instance()->getItemByName(currman, name);
	bool success = currman->removeItemById(curr.id);
	delete currman;
	return success;
}
