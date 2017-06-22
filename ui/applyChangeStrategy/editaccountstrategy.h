#ifndef EDITACCOUNTSTRATEGY_H
#define EDITACCOUNTSTRATEGY_H

#include "dao/accountmanager.h"
#include "applychangestrategy.h"

class editAccountStrategy : public applyChangeStrategy
{
public:
	using applyChangeStrategy::applyChangeStrategy;
	virtual bool applyChange();
	virtual bool applyDelete();
};

#endif // EDITACCOUNTSTRATEGY_H
