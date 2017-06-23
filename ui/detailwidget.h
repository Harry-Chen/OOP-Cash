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
  * @file detailwidget.h
  * @author Harry Chen <harry-chen@outlook.com>
  * @author Zeping Niu <nnznk12@gmail.com>
  * @date 2017.5
  * @brief Header file for class DetailWidget
  */

#ifndef DETAILWIDGET_H
#define DETAILWIDGET_H

#include <QWidget>
#include <QVector>
#include <QtAlgorithms>

#include "dao/usermanager.h"
#include "dao/billmanager.h"
#include "model/bill.h"
#include "plot/balanceplotsystem.h"
#include "recordcostearnwidget.h"

namespace Ui {
class DetailWidget;
}

/**
 * @brief A Widget to show the detail of a list of bills
 */
class DetailWidget : public QWidget
{
    Q_OBJECT
public slots:
	/**
	 * @brief fillData
	 * @details fill at most 100 QListWidgetItem to the BillList at a time
	 */
	void fillData();
	/**
	 * @brief consult this function is called iff the bill list needs to be refeshed
	 */
	void consult();
    void plot();
	/**
     * @brief remove Bill of certain ID
	 * @param billId the id of bill to be removed
	 */
	void removeBill(ID billId);
	void editBill(Bill* pBill);
signals:
	void fillFinished(bool finished);
	void addingFinished();
public:
	/**
     * @brief fill the widget with the data in given QVector<Bill>
	 * @param parent the parent widget
	 * @param _userman the pointer of UserManager
	 */
	explicit DetailWidget(QWidget *parent, UserManager *_userman);
    ~DetailWidget();
private:
	int currentNum;
	const int ItemAddPerTime = 60;
    Ui::DetailWidget *ui;
    UserManager *userman;
	QVector<Bill> billVector;
	QMap<ID, Account> allAccount;
	QMap<ID, Category> allCategory;
};

#endif // DETAILWIDGET_H
