#include "edititemwidgetfactory.h"

editItemWidgetFactory::editItemWidgetFactory(UserManager* userman)
{
	_userman = userman;
}

editItemWidget*editItemWidgetFactory::getNewAccountWidget(QWidget* parent)
{
	QStringList labnamelist;
	labnamelist << "新建账户" << "货币" << "新帐户名" << "";
	QVector<bool> labvisiblelist;
	labvisiblelist << true << true << true << false;
	QVector<bool> btnEnableList;
	btnEnableList << false << true << true;
	auto ans = buildWidget(parent, "新建账户", labnamelist, labvisiblelist, "", "", false, true, btnEnableList);
	ans->setApplyChangeStrategy(new addAccountStrategy(ans, _userman));
	return ans;
}

editItemWidget*editItemWidgetFactory::getEditAccountWidget(QWidget* parent, const QString& accName)
{
	QStringList labnamelist;
	labnamelist << accName << "货币" << "修改账户名" << "";
	QVector<bool> labvisiblelist;
	labvisiblelist << true << true << true << false;
	QVector<bool> btnEnableList;
	btnEnableList << true << true << true;
	auto ans = buildWidget(parent, "编辑账户", labnamelist, labvisiblelist, "", "", false, true, btnEnableList);
	ans->setApplyChangeStrategy(new editAccountStrategy(ans, _userman));
	return ans;
}

editItemWidget*editItemWidgetFactory::getNewCurrencyWidget(QWidget* parent)
{
	QStringList labnamelist;
	labnamelist << "新建货币种类" << "" << "货币名" << "汇率";
	QVector<bool> labvisiblelist;
	labvisiblelist << true << false << true << true;
	QVector<bool> btnEnableList;
	btnEnableList << false << true << true;
	auto ans = buildWidget(parent, "新建货币", labnamelist, labvisiblelist, "", "", true, true, btnEnableList, false);
	ans->setApplyChangeStrategy(new addCurrencyStrategy(ans, _userman));
	return ans;
}

editItemWidget*editItemWidgetFactory::getNewCategoryWidget(QWidget* parent)
{
	QStringList labnamelist;
	labnamelist << "新建消费种类" << "" << "消费种类名称" << "";
	QVector<bool> labvisiblelist;
	labvisiblelist << true << false << true << false;
	QVector<bool> btnEnableList;
	btnEnableList << false << true << true;
	auto ans = buildWidget(parent, "新建种类", labnamelist, labvisiblelist, "", "", false, true, btnEnableList, false);
	ans->setApplyChangeStrategy(new addCategoryStrategy(ans, _userman));
	return ans;
}

editItemWidget*editItemWidgetFactory::getEditCategoryWidget(QWidget* parent, const QString& cateName)
{
	QStringList labnamelist;
	labnamelist << cateName << "" << "新名称" << "";
	QVector<bool> labvisiblelist;
	labvisiblelist << true << false << true << false;
	QVector<bool> btnEnableList;
	btnEnableList << false << true << true;
	auto ans = buildWidget(parent, "编辑种类", labnamelist, labvisiblelist, "", "", false, true, btnEnableList, false);
	ans->setApplyChangeStrategy(new editCategoryStrategy(ans, _userman));
	return ans;
}

editItemWidget*editItemWidgetFactory::getEditCurrencyWidget(QWidget* parent, const QString& currName)
{
	QStringList labnamelist;
	labnamelist << currName << "" << "修改货币名" << "修改汇率";
	QVector<bool> labvisiblelist;
	labvisiblelist << true << false << true << true;
	QVector<bool> btnEnableList;
	btnEnableList << true << true << true;
	auto ans = buildWidget(parent, "编辑货币", labnamelist, labvisiblelist, "", "", true, true, btnEnableList, false);
	ans->setApplyChangeStrategy(new editCurrencyStrategy(ans, _userman));
	return ans;
}

editItemWidget* editItemWidgetFactory::buildWidget(QWidget* parent, const QString& title, \
										const QStringList& labnamelist, \
										const QVector<bool>& labvisiblelist,\
										const QString& defaultText2, \
										const QString& defaultText3,
										bool line2visible, \
										bool line3visible,\
										const QVector<bool>& btnEnableList, \
										bool currComboBoxVisible)
{
	auto result = new editItemWidget(_userman, parent);
	result->setWindowTitle(title);
	result->setLabelName(*(result->getlabelVector()), labnamelist, labvisiblelist) \
		->setCurrencyComboBox(currComboBoxVisible) \
		->setLineEdit2(defaultText2, line2visible) \
		->setLineEdit3(defaultText3, line3visible) \
		->setDeleteBtn(btnEnableList[0]) \
		->setConformBtn(btnEnableList[1]) \
		->setCancelBtn(btnEnableList[2]); \
	return result;
}
