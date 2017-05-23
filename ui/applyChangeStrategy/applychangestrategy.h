#ifndef APPLYCHANGESTRATEGY_H
#define APPLYCHANGESTRATEGY_H

#include "../edititemwidget.h"
#include "dao/usermanager.h"

class applyChangeStrategy
{
public:
	applyChangeStrategy(editItemWidget* w, UserManager* userman);
	virtual void applyChange() = 0;
protected:
	editItemWidget* _w;
	UserManager* _userman;
};

#endif // APPLYCHANGESTRATEGY_H
