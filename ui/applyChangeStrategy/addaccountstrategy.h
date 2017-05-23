#ifndef ADDACCOUNTSTRATEGY_H
#define ADDACCOUNTSTRATEGY_H

#include "applychangestrategy.h"

class addAccountStrategy : public applyChangeStrategy
{
public:
	using applyChangeStrategy::applyChangeStrategy;
	virtual void applyChange();
};

#endif // ADDACCOUNTSTRATEGY_H
