/**
 * Copyright 2017 OOP-Cash Team

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   edititemwidgetfactory.cpp
 * @author Zeping Niu <nnznk12@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class EditItemFactory
 */


#include "edititemwidgetfactory.h"

EditItemWidgetFactory::EditItemWidgetFactory(UserManager* userman)
{
	_userman = userman;
}

EditItemWidget*EditItemWidgetFactory::getNewAccountWidget(QWidget* parent)
{
	QStringList labnamelist;
    labnamelist << QObject::tr("新建账户") << QObject::tr("货币") << QObject::tr("新帐户名") << "";
	QVector<bool> labvisiblelist;
	labvisiblelist << true << true << true << false;
	QVector<bool> btnEnableList;
	btnEnableList << false << true << true;
    auto ans = buildWidget(parent, QObject::tr("新建账户"), labnamelist, labvisiblelist, "", "", false, true, btnEnableList);
	ans->setApplyChangeStrategy(new AddAccountStrategy(ans, _userman));
	return ans;
}

EditItemWidget*EditItemWidgetFactory::getEditAccountWidget(QWidget* parent, const QString& accName)
{
	QStringList labnamelist;
    labnamelist << accName << QObject::tr("货币") << QObject::tr("修改账户名") << "";
	QVector<bool> labvisiblelist;
	labvisiblelist << true << true << true << false;
	QVector<bool> btnEnableList;
	btnEnableList << true << true << true;
    auto ans = buildWidget(parent, QObject::tr("编辑账户"), labnamelist, labvisiblelist, "", "", false, true, btnEnableList);
	ans->setApplyChangeStrategy(new EditAccountStrategy(ans, _userman));
	return ans;
}

EditItemWidget*EditItemWidgetFactory::getNewCurrencyWidget(QWidget* parent)
{
	QStringList labnamelist;
    labnamelist << QObject::tr("新建货币种类") << "" << QObject::tr("货币名") << QObject::tr("汇率");
	QVector<bool> labvisiblelist;
	labvisiblelist << true << false << true << true;
	QVector<bool> btnEnableList;
	btnEnableList << false << true << true;
    auto ans = buildWidget(parent, QObject::tr("新建货币种类"), labnamelist, labvisiblelist, "", "", true, true, btnEnableList, false);
	ans->setApplyChangeStrategy(new AddCurrencyStrategy(ans, _userman));
	return ans;
}

EditItemWidget*EditItemWidgetFactory::getNewCategoryWidget(QWidget* parent)
{
	QStringList labnamelist;
    labnamelist << QObject::tr("新建消费种类") << "" << QObject::tr("消费种类名称") << "";
	QVector<bool> labvisiblelist;
	labvisiblelist << true << false << true << false;
	QVector<bool> btnEnableList;
	btnEnableList << false << true << true;
    auto ans = buildWidget(parent, QObject::tr("新建消费种类"), labnamelist, labvisiblelist, "", "", false, true, btnEnableList, false);
	ans->setApplyChangeStrategy(new AddCategoryStrategy(ans, _userman));
	return ans;
}

EditItemWidget*EditItemWidgetFactory::getEditCategoryWidget(QWidget* parent, const QString& cateName)
{
	QStringList labnamelist;
    labnamelist << cateName << "" << QObject::tr("新名称") << "";
	QVector<bool> labvisiblelist;
	labvisiblelist << true << false << true << false;
	QVector<bool> btnEnableList;
	btnEnableList << true << true << true;
    auto ans = buildWidget(parent, QObject::tr("编辑种类"), labnamelist, labvisiblelist, "", "", false, true, btnEnableList, false);
	ans->setApplyChangeStrategy(new EditCategoryStrategy(ans, _userman));
	return ans;
}

EditItemWidget*EditItemWidgetFactory::getEditCurrencyWidget(QWidget* parent, const QString& currName)
{
	QStringList labnamelist;
    labnamelist << currName << "" << QObject::tr("修改货币名") << QObject::tr("修改汇率");
	QVector<bool> labvisiblelist;
	labvisiblelist << true << false << true << true;
	QVector<bool> btnEnableList;
	btnEnableList << true << true << true;
    auto ans = buildWidget(parent, QObject::tr("编辑货币"), labnamelist, labvisiblelist, "", "", true, true, btnEnableList, false);
	ans->setApplyChangeStrategy(new EditCurrencyStrategy(ans, _userman));
	return ans;
}

EditItemWidget* EditItemWidgetFactory::buildWidget(QWidget* parent, const QString& title, \
										const QStringList& labnamelist, \
										const QVector<bool>& labvisiblelist,\
										const QString& defaultText2, \
										const QString& defaultText3,
										bool line2visible, \
										bool line3visible,\
										const QVector<bool>& btnEnableList, \
										bool currComboBoxVisible)
{
	auto result = new EditItemWidget(_userman, parent);
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
