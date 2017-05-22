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
	static ItemSearcher* instance() {
		if(!_instance) {
			_instance = new ItemSearcher;
		}
		return _instance;
	}

	//只需要ItemManager管理的类有name字段即可
	template<typename T>
	void getNameList(ItemManager<T>* man, QStringList& result)
	{
		//从manager中得到stringlist, 将具体getAllItem采用容器类型这一变化隔离出来
		auto itemMap = man->getAllItems(); //模板使得这一方法可以支持T中有name字段的全部情况
		//在没有name字段时会编译错误
		for(auto iter = itemMap.constBegin(); iter != itemMap.constEnd(); ++iter) {
			result << iter.value().name;
		}
	}
	//条件同上
	template<typename T>
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


