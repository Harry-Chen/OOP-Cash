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
 * @file   addcategorystrategy.cpp
 * @author Zeping Niu <nnznk12@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class AddCategoryStrategy
 */


#include "addcategorystrategy.h"

bool AddCategoryStrategy::applyChange()
{
	QString name = _w->getLineEditText2();
	Category cate(-1, name, _userman->getLoggedInUid());
	auto cateman = new CategoryManager(_userman);
	bool success = (cateman->addItem(cate) != -1);
	delete cateman;
	return success;
}

bool AddCategoryStrategy::applyDelete()
{
	return true;
}
