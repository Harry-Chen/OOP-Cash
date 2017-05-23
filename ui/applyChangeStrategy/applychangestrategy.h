#ifndef APPLYCHANGESTRATEGY_H
#define APPLYCHANGESTRATEGY_H

#include "../edititemwidget.h"
#include "dao/usermanager.h"

class applyChangeStrategy
{
public:
	applyChangeStrategy(editItemWidget* w, UserManager* userman);
	virtual bool applyChange() = 0;
	virtual bool applyDelete() = 0;
protected:
	editItemWidget* _w;
	UserManager* _userman;
};

#endif // APPLYCHANGESTRATEGY_H
