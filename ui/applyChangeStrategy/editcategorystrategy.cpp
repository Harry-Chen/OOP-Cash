#include "editcategorystrategy.h"

void editCategoryStrategy::applyChange()
{
	auto cateman = new CategoryManager(_userman);
	QString oldName = _w->getLabelText(0);
	QString newName = _w->getLineEditText2();
	Category cate = ItemSearcher::instance()->getItemByName(cateman, oldName);
	cate.name = newName;
	cateman->modifyItem(cate);
	delete cateman;
}
