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
 * @file   addaccountstrategy.cpp
 * @author Zeping Niu <nnznk12@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class AddAccountStrategy
 */


#include "addaccountstrategy.h"

bool AddAccountStrategy::applyChange()
{
	QString newName = _w->getLineEditText2();
	QString currName = _w->getComboboxText();
	auto currman = new CurrencyManager(_userman);
	Currency curr = ItemSearcher::instance()->getItemByName(currman, currName);
	delete currman;
	Account acc(-1, newName, _userman->getLoggedInUid(), curr.id);
	auto accman = new AccountManager(_userman);
	bool success = (accman->addItem(acc) != -1);
	delete accman;
	return success;
}

bool AddAccountStrategy::applyDelete()
{
	return true;
}
