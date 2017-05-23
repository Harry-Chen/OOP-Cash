#ifndef ADDCATEGORYSTRATEGY_H
#define ADDCATEGORYSTRATEGY_H

#include "applychangestrategy.h"

class addCategoryStrategy : public applyChangeStrategy
{
public:
	using applyChangeStrategy::applyChangeStrategy;
	virtual void applyChange();
	virtual void applyDelete();
};

#endif // ADDCATEGORYSTRATEGY_H
