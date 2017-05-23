#include "addcurrencystrategy.h"

void addCurrencyStrategy::applyChange()
{
	QString name = _w->getLineEditText1();
	double rate = _w->getLineEditText2().toDouble();
	Currency curr(-1, _userman->getLoggedInUid(), name, rate);
	auto currman = new CurrencyManager(_userman);
	currman->addItem(curr);
	delete currman;
}
