#ifndef ADDACCOUNTSTRATEGY_H
#define ADDACCOUNTSTRATEGY_H

#include "applychangestrategy.h"

class addAccountStrategy : public applyChangeStrategy
{
public:
	using applyChangeStrategy::applyChangeStrategy;
	virtual bool applyChange();
	virtual bool applyDelete();
};

#endif // ADDACCOUNTSTRATEGY_H
