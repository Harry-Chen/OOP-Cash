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
  * @file itemseacher.h
  * @author Zeping Niu <nnznk12@gmail.com>
  * @date 2017.5
  * @brief Header file for class ItemSeacher
  */


#ifndef ITEMSEARCHER_H
#define ITEMSEARCHER_H

#include "dao/accountmanager.h"
#include "dao/billmanager.h"
#include "dao/categorymanager.h"
#include "dao/currencymanager.h"
#include "dao/itemmanager.h"
#include "dao/usermanager.h"


class ItemSearcher
{
public:
	/**
	 * @brief instance
	 * @return the pointer of ItemSearcher
	 */
	static ItemSearcher* instance() {
		if(!_instance) {
			_instance = new ItemSearcher;
		}
		return _instance;
	}

	//只需要ItemManager管理的类有name字段即可
	template<typename T>
	/**
	 * @brief get the name list of a kind of item
	 * @param man pointer of ItemManager
	 * @param result the list of item names
	 */
	void getNameList(ItemManager<T>* man, QStringList& result)
	{
		//从manager中得到stringlist, 将具体getAllItem采用容器类型这一变化隔离出来
		auto itemMap = man->getAllItems(); //模板使得这一方法可以支持T中有name字段的全部情况
		//在没有name字段时会编译错误
		for(auto iter = itemMap.constBegin(); iter != itemMap.constEnd(); ++iter) {
			result << iter.value().name;
		}
	}

	template<typename T>
	/**
	 * @brief get the item by its name
	 * @param man pointer of ItemManager
	 * @param str the name of the item
	 * @return the item(return 0 if not found)
	 */
	T getItemByName(ItemManager<T>* man, const QString& str) {
		auto map = man->getAllItems();
		for(auto iter = map.constBegin(); iter != map.constEnd(); ++iter) {
			if(iter.value().name == str) {
				return iter.value(); //得到item
			}
		}
		return T(0);
	}
private:
	ItemSearcher() {}
	static ItemSearcher* _instance;
};

#endif // ITEMSEARCHER_H


