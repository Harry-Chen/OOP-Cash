#include "editcategorystrategy.h"

bool editCategoryStrategy::applyChange()
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

bool editCategoryStrategy::applyDelete()
{
	auto cateman = new CategoryManager(_userman);
	QString name = _w->getLabelText(0);
	Category cate = ItemSearcher::instance()->getItemByName(cateman, name);
	bool success = cateman->removeItemById(cate.id);
	delete cateman;
	return success;
}
