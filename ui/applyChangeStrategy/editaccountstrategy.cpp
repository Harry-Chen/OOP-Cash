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
 * @file   editaccountstrategy.cpp
 * @author Zeping Niu <nnznk12@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class EditAccountStrategy
 */


#include "editaccountstrategy.h"

bool EditAccountStrategy::applyChange()
{
	QString oldName = _w->getLabelText(0); ///< old name of account
	QString currName = _w->getComboboxText(); ///< name of currency used by this account
	auto accman = new AccountManager(_userman);
	auto currman = new CurrencyManager(_userman);
	Account acc = ItemSearcher::instance()->getItemByName(accman, oldName);
	Currency curr = ItemSearcher::instance()->getItemByName(currman, currName);
	QString newName = _w->getLineEditText2(); ///< new name of account
	acc.name = newName;
	acc.cid = curr.id;
	bool success = accman->modifyItem(acc);
	delete currman;
	delete accman;
	return success;
}

bool EditAccountStrategy::applyDelete()
{
	auto accman = new AccountManager(_userman);
	QString name = _w->getLabelText(0);
	Account acc = ItemSearcher::instance()->getItemByName(accman, name);
	bool success = accman->removeItemById(acc.id);
	delete accman;
	return success;
}
