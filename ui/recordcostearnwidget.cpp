#include "recordcostearnwidget.h"

RecordCostEarnWidget::RecordCostEarnWidget(QWidget* parent):ChangeBillWidget(parent)
{
	isCost = true;
	QRadioButton* cbtn = getCostBtn();
	QRadioButton* ebtn = getEarnBtn();
	cbtn->setVisible(true);
	ebtn->setVisible(true);
	connect(cbtn, SIGNAL(toggled(bool)), this, SLOT(setIsCostTrue()));
	connect(ebtn, SIGNAL(toggled(bool)), this, SLOT(setIsCostFalse()));
}

void RecordCostEarnWidget::addBill()
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
	int money;
	if(getMoneyLineEdit()->hasAcceptableInput()) {
		money = int(getMoneyLineEdit()->text().toDouble() * 100);
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
	if(isCost) {
		newbill->from = acc.id;
	} else {
		newbill->to = acc.id;
	}
	if(billman->addItem(*newbill) == -1) {
		QMessageBox::information(this, "Sorry", "the bill cannot be saved!");
	} else {
		QMessageBox::information(this, "info", "the bill have been saved!");
		clearWidget();
	}
}

void RecordCostEarnWidget::setIsCostFalse()
{
	isCost = false;
	setLabelNames();
}

void RecordCostEarnWidget::setIsCostTrue()
{
	isCost = true;
	setLabelNames();
}

void RecordCostEarnWidget::setLabelNames()
{
	if(isCost) {
		setCostLabelNames();
	} else {
		setEarnLabelNames();
	}
}

void RecordCostEarnWidget::setCombobox1()
{
	CategoryManager* cateman = new CategoryManager(_userman);
	QStringList cateList;
	ItemSearcher::instance()->getNameList(cateman, cateList); // 从manager直接得到StringList
	getCombobox1()->clear();
	getCombobox1()->addItems(cateList);
}

void RecordCostEarnWidget::setCombobox2()
{
	AccountManager* accman = new AccountManager(_userman);
	QStringList accList;
	ItemSearcher::instance()->getNameList(accman, accList);
	getCombobox2()->clear();
	getCombobox2()->addItems(accList);
}

void RecordCostEarnWidget::setCostLabelNames()
{
	getLabel1()->setText("账目分类");
	getLabel2()->setText("支出账户");
	getLabel3()->setText("支出金额");
}

void RecordCostEarnWidget::setEarnLabelNames()
{
	getLabel1()->setText("账目分类");
	getLabel2()->setText("收入账户");
	getLabel3()->setText("收入金额");
}
