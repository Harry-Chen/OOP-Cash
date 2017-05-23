#include "recordcostwidget.h"

RecordCostWidget::RecordCostWidget(QWidget* parent):ChangeBillWidget(parent)
{

}

void RecordCostWidget::addBill()
{
	auto cateman = new CategoryManager(_userman);
	auto accman = new AccountManager(_userman);
	auto currman = new CurrencyManager(_userman);

	auto cate = ItemSearcher::instance()->getItemByName(cateman, getCombobox1()->currentText());
	auto acc = ItemSearcher::instance()->getItemByName(accman, getCombobox2()->currentText());
	auto curr = ItemSearcher::instance()->getItemByName(currman, getCurrencyCombobox()->currentText());
	delete cateman;
	delete accman;
	delete currman;

	bool valid = true;

	QDate date = QDate::fromString(getTimeLineEdit()->text(), "yyyy-MM-dd");
	if(!date.isValid()) {
		QMessageBox::information(this, "Attention", "please input valid date and the date should be yyyy-MM-dd format");
		valid = false;
	}
	double money;
	if(getMoneyLineEdit()->hasAcceptableInput()) {
		money = getMoneyLineEdit()->text().toDouble();
	} else {
		QMessageBox::information(this, "Attention", "the money should be double!");
		valid = false;
	}

	if(!valid) {
		return;
	} //else

	auto billman = new BillManager(_userman);
	auto newbill = new Bill(-1, acc.id, -1, _userman->getLoggedInUid(),\
						 cate.id, money, curr.id, QDateTime::currentDateTime(),\
						  true, date, getNoteTextEdit()->toPlainText());
	if(billman->addItem(*newbill) == -1) {
		QMessageBox::information(this, "Sorry", "the bill cannot be saved!");
	} else {
		QMessageBox::information(this, "info", "the bill have been saved!");
		clearWidget();
	}
}

void RecordCostWidget::setLabelNames()
{
	getLabel1()->setText(QStringLiteral("账目分类"));
	getLabel2()->setText(QStringLiteral("支出账户"));
	getLabel3()->setText(QStringLiteral("支出金额"));
}

void RecordCostWidget::setCombobox1()
{
	CategoryManager* cateman = new CategoryManager(_userman);
	QStringList cateList;
	ItemSearcher::instance()->getNameList(cateman, cateList); // 从manager直接得到StringList
	getCombobox1()->clear();
	getCombobox1()->addItems(cateList);
}

void RecordCostWidget::setCombobox2()
{
	AccountManager* accman = new AccountManager(_userman);
	QStringList accList;
	ItemSearcher::instance()->getNameList(accman, accList);
	getCombobox2()->clear();
	getCombobox2()->addItems(accList);
}
