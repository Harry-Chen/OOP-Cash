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
 * @file   addcurrencystrategy.cpp
 * @author Zeping Niu <nnznk12@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class AddCurrencyStrategy
 */


#include "addcurrencystrategy.h"

bool AddCurrencyStrategy::applyChange()
{
	QString name = _w->getLineEditText1(); ///< new currency name
	double rate = _w->getLineEditText2().toDouble(); ///< currency rate
	Currency curr(-1, _userman->getLoggedInUid(), name, rate); ///< new currency
	auto currman = new CurrencyManager(_userman);
	bool success = (currman->addItem(curr) != -1);
	delete currman;
	return success;
}

bool AddCurrencyStrategy::applyDelete()
{
	return true;
}
