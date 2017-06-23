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
 * @file   billdetailwidget.h
 * @author Harry Chen <harry-chen@outlook.com>
 * @author Zeping Niu <nnznk12@gmail.com>
 * @date   2017.05
 * @brief  Header file of class BillDetailWidget
 */


#ifndef BILLDETAILWIDGET_H
#define BILLDETAILWIDGET_H

#include <QWidget>
#include <QMessageBox>
#include <QListWidget>
#include "model/bill.h"
#include "dao/usermanager.h"
#include "dao/categorymanager.h"
#include "dao/accountmanager.h"

namespace Ui {
class BillDetailWidget;
}

/**
 * @brief Widget to show the detail info of one specific Bill
 */

class BillDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BillDetailWidget(QWidget *parent = 0);
	/**
	 * @brief fill the widget with data provided
	 * @param bill the Bill to display
	 * @param allAccounts ID-Account Map of all accounts
	 * @param allCategories ID-Category Map of all categories
	 */
	void fillData(const Bill& bill, const QMap<ID, Account>& allAccounts, const QMap<ID, Category>& allCategories);
    ~BillDetailWidget();
signals:
	/**
	 * @brief pass the bill id to the DetailWidget to delete bill in sqlite
	 * @param billId
	 */
	void delBillSignal(ID billId);
	void editBillSignal(Bill* pBill);
private slots:
	/**
	 * @brief on_removeButton_clicked
	 * @details when the remove button is clicked, this slot function will ask the user whether to remove the bill
	 */
	void on_removeButton_clicked();
	/**
	 * @brief on_editButton_clicked
	 */
	void on_editButton_clicked();

private:
    Ui::BillDetailWidget *ui;
	Bill _bill;
};

#endif // BILLDETAILWIDGET_H
