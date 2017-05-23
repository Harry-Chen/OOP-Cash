#ifndef EDITCURRENCYSTRATEGY_H
#define EDITCURRENCYSTRATEGY_H

#include "applychangestrategy.h"

class editCurrencyStrategy : public applyChangeStrategy
{
public:
	using applyChangeStrategy::applyChangeStrategy;
	virtual void applyChange();
	virtual void applyDelete();
};

#endif // EDITCURRENCYSTRATEGY_H
