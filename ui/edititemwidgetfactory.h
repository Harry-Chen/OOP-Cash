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

class editItemWidgetFactory
{
public:
	editItemWidgetFactory(UserManager* userman);
	editItemWidget* getNewAccountWidget(QWidget* parent);
	editItemWidget* getEditAccountWidget(QWidget* parent, const QString& accName);
	editItemWidget* getNewCurrencyWidget(QWidget* parent);
	editItemWidget* getEditCurrencyWidget(QWidget* parent, const QString& currName);
	editItemWidget* getNewCategoryWidget(QWidget* parent);
	editItemWidget* getEditCategoryWidget(QWidget* parent, const QString& cateName);
private:
	UserManager* _userman;
	editItemWidget* buildWidget(QWidget* parent, const QString& title, \
					 const QStringList& namelist, const QVector<bool>& labvisiblelist, \
					 const QString& defaultText2, const QString& defaultText3, \
					 bool line2visible, bool line3visible, \
					 const QVector<bool>& btnEnableList, bool currComboBoxVisible = true);
};

#endif // EDITITEMWIDGETFACTORY_H
