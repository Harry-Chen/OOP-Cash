#include "editcurrencystrategy.h"

bool editCurrencyStrategy::applyChange()
{
	QString oldName = _w->getLabelText(0);
	QString newName = _w->getLineEditText1();
	double newRate = _w->getLineEditText2().toDouble();
	auto currman = new CurrencyManager(_userman);
	Currency curr = ItemSearcher::instance()->getItemByName(currman, oldName);
	curr.name = newName;
	curr.rate = newRate;
	bool success = currman->modifyItem(curr);
	delete currman;
	return success;
}

bool editCurrencyStrategy::applyDelete()
{
	QString name = _w->getLabelText(0);
	auto currman = new CurrencyManager(_userman);
	Currency curr = ItemSearcher::instance()->getItemByName(currman, name);
	bool success = currman->removeItemById(curr.id);
	delete currman;
	return success;
}
