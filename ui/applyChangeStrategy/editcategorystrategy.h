#ifndef EDITCATEGORYSTRATEGY_H
#define EDITCATEGORYSTRATEGY_H

#include "applychangestrategy.h"

class editCategoryStrategy : public applyChangeStrategy
{
public:
	using applyChangeStrategy::applyChangeStrategy;
	virtual bool applyChange();
	virtual bool applyDelete();
};

#endif // EDITCATEGORYSTRATEGY_H
