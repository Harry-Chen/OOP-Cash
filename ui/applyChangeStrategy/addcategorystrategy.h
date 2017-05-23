#ifndef ADDCATEGORYSTRATEGY_H
#define ADDCATEGORYSTRATEGY_H

#include "applychangestrategy.h"

class addCategoryStrategy : public applyChangeStrategy
{
public:
	using applyChangeStrategy::applyChangeStrategy;
	virtual bool applyChange();
	virtual bool applyDelete();
};

#endif // ADDCATEGORYSTRATEGY_H
