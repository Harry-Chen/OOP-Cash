#include "editaccountstrategy.h"

void editAccountStrategy::applyChange()
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
	accman->modifyItem(acc);
	delete currman;
	delete accman;
}
