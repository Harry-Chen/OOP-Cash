#ifndef EDITCATEGORYSTRATEGY_H
#define EDITCATEGORYSTRATEGY_H

#include "applychangestrategy.h"

class editCategoryStrategy : public applyChangeStrategy
{
public:
	using applyChangeStrategy::applyChangeStrategy;
	virtual void applyChange();
};

#endif // EDITCATEGORYSTRATEGY_H
