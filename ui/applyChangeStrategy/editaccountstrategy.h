#ifndef EDITACCOUNTSTRATEGY_H
#define EDITACCOUNTSTRATEGY_H

#include "applychangestrategy.h"
#include "dao/accountmanager.h"

class editAccountStrategy : public applyChangeStrategy
{
public:
	using applyChangeStrategy::applyChangeStrategy;
	virtual bool applyChange();
	virtual bool applyDelete();
};

#endif // EDITACCOUNTSTRATEGY_H
