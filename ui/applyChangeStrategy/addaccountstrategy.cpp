#include "addaccountstrategy.h"

bool addAccountStrategy::applyChange()
{
	QString newName = _w->getLineEditText2();
	QString currName = _w->getComboboxText();
	auto currman = new CurrencyManager(_userman);
	Currency curr = ItemSearcher::instance()->getItemByName(currman, currName);
	delete currman;
	Account acc(-1, newName, _userman->getLoggedInUid(), curr.id);
	auto accman = new AccountManager(_userman);
	bool success = (accman->addItem(acc) != -1);
	delete accman;
	return success;
}

bool addAccountStrategy::applyDelete()
{
	return true;
}
