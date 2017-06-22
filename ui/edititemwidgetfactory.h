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
  * @file edititemwidgetfactory.h
  * @author Zeping Niu <nnznk12@gmail.com>
  * @date 2017.5
  * @brief Header file for class EditItemFactroy
  */


#ifndef EDITITEMWIDGETFACTORY_H
#define EDITITEMWIDGETFACTORY_H

#include "dao/usermanager.h"
#include "applyChangeStrategy/applychangestrategy.h"
#include "applyChangeStrategy/editaccountstrategy.h"
#include "applyChangeStrategy/editcategorystrategy.h"
#include "applyChangeStrategy/editcurrencystrategy.h"
#include "applyChangeStrategy/addaccountstrategy.h"
#include "applyChangeStrategy/addcategorystrategy.h"
#include "applyChangeStrategy/addcurrencystrategy.h"

#include "edititemwidget.h"

class EditItemWidgetFactory
{
public:
	EditItemWidgetFactory(UserManager* userman);
	EditItemWidget* getNewAccountWidget(QWidget* parent);
	EditItemWidget* getEditAccountWidget(QWidget* parent, const QString& accName);
	EditItemWidget* getNewCurrencyWidget(QWidget* parent);
	EditItemWidget* getEditCurrencyWidget(QWidget* parent, const QString& currName);
	EditItemWidget* getNewCategoryWidget(QWidget* parent);
	EditItemWidget* getEditCategoryWidget(QWidget* parent, const QString& cateName);
private:
	UserManager* _userman;
	EditItemWidget* buildWidget(QWidget* parent, const QString& title, \
					 const QStringList& namelist, const QVector<bool>& labvisiblelist, \
					 const QString& defaultText2, const QString& defaultText3, \
					 bool line2visible, bool line3visible, \
					 const QVector<bool>& btnEnableList, bool currComboBoxVisible = true);
};

#endif // EDITITEMWIDGETFACTORY_H
