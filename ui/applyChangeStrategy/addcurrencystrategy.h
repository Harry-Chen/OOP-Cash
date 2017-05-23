#ifndef ADDCURRENCYSTRATEGY_H
#define ADDCURRENCYSTRATEGY_H

#include "applychangestrategy.h"

class addCurrencyStrategy : public applyChangeStrategy
{
public:
	using applyChangeStrategy::applyChangeStrategy;
	virtual void applyChange();
	virtual void applyDelete();
};

#endif // ADDCURRENCYSTRATEGY_H
