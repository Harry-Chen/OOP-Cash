#include "editaccountstrategy.h"

bool editAccountStrategy::applyChange()
{
	QString oldName = _w->getLabelText(0);
	QString currName = _w->getComboboxText();
	auto accman = new AccountManager(_userman);
	auto currman = new CurrencyManager(_userman);
	Account acc = ItemSearcher::instance()->getItemByName(accman, oldName);
	Currency curr = ItemSearcher::instance()->getItemByName(currman, currName);
	QString newName = _w->getLineEditText2();
	acc.name = newName;
	acc.cid = curr.id;
	bool success = accman->modifyItem(acc);
	delete currman;
	delete accman;
	return success;
}

bool editAccountStrategy::applyDelete()
{
	auto accman = new AccountManager(_userman);
	QString name = _w->getLabelText(0);
	Account acc = ItemSearcher::instance()->getItemByName(accman, name);
	bool success = accman->removeItemById(acc.id);
	delete accman;
	return success;
}
