#include "recordcostwidget.h"

RecordCostWidget::RecordCostWidget()
{

}

void RecordCostWidget::addBill()
{
	BillManager billman = new BillManager(_userman);

}

void RecordCostWidget::setLabelNames()
{
	getLabel1()->setText(QString("账目分类"));
	getLabel2()->setText(QString("支出账户"));
	getLabel3()->setText(QString("支出金额"));
}

void RecordCostWidget::setCombobox1()
{
	CategoryManager* cateman = new CategoryManager(_userman);
	QStringList cateList;
	ChangeBillWidget::getNameList(cateman, cateList); // 从manager直接得到StringList
	getCombobox1()->clear();
	getCombobox1()->addItems(cateList);
}

void RecordCostWidget::setCombobox2()
{
	AccountManager* accman = new AccountManager(_userman);
	QStringList accList;
	ChangeBillWidget::getNameList(accman, accList);
	getCombobox2()->clear();
	getCombobox2()->addItems(accList);
}
