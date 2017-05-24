#ifndef EDITCURRENCYSTRATEGY_H
#define EDITCURRENCYSTRATEGY_H

#include "applychangestrategy.h"

class editCurrencyStrategy : public applyChangeStrategy
{
public:
	using applyChangeStrategy::applyChangeStrategy;
	virtual bool applyChange();
	virtual bool applyDelete();
};

#endif // EDITCURRENCYSTRATEGY_H
