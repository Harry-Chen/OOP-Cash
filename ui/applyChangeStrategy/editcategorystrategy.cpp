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
 * @file  editcategorystrategy.cpp
 * @author Zeping Niu <nnznk12@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class EditCategoryStrategy
 */


#include "editcategorystrategy.h"

bool EditCategoryStrategy::applyChange()
{
	auto cateman = new CategoryManager(_userman);
	QString oldName = _w->getLabelText(0);
	QString newName = _w->getLineEditText2();
	Category cate = ItemSearcher::instance()->getItemByName(cateman, oldName);
	cate.name = newName;
	bool success = cateman->modifyItem(cate);
	delete cateman;
	return success;
}

bool EditCategoryStrategy::applyDelete()
{
	auto cateman = new CategoryManager(_userman);
	QString name = _w->getLabelText(0);
	Category cate = ItemSearcher::instance()->getItemByName(cateman, name);
	bool success = cateman->removeItemById(cate.id);
	delete cateman;
	return success;
}
