#include "addcategorystrategy.h"

bool addCategoryStrategy::applyChange()
{
	QString name = _w->getLineEditText2();
	Category cate(-1, name, _userman->getLoggedInUid());
	auto cateman = new CategoryManager(_userman);
	bool success = (cateman->addItem(cate) != -1);
	delete cateman;
	return success;
}

bool addCategoryStrategy::applyDelete()
{
	return true;
}
