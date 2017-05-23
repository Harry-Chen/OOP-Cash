#include "addcategorystrategy.h"

void addCategoryStrategy::applyChange()
{
	QString name = _w->getLineEditText2();
	Category cate(-1, name, _userman->getLoggedInUid());
	auto cateman = new CategoryManager(_userman);
	cateman->addItem(cate);
	delete cateman;
}

void addCategoryStrategy::applyDelete() {}
