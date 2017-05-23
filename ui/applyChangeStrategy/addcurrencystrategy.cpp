#include "addcurrencystrategy.h"

bool addCurrencyStrategy::applyChange()
{
	QString name = _w->getLineEditText1();
	double rate = _w->getLineEditText2().toDouble();
	Currency curr(-1, _userman->getLoggedInUid(), name, rate);
	auto currman = new CurrencyManager(_userman);
	bool success = (currman->addItem(curr) != -1);
	delete currman;
	return success;
}

bool addCurrencyStrategy::applyDelete()
{
	return true;
}
