#include "editcurrencystrategy.h"

void editCurrencyStrategy::applyChange()
{
	QString oldName = _w->getLabelText(0);
	QString newName = _w->getLineEditText1();
	double newRate = _w->getLineEditText2().toDouble();
	auto currman = new CurrencyManager(_userman);
	Currency curr = ItemSearcher::instance()->getItemByName(currman, oldName);
	curr.name = newName;
	curr.rate = newRate;
	currman->modifyItem(curr);
	delete currman;
}
