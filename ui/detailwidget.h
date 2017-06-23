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
  * @file addaccountstrategy.h
  * @author ...
  * @author Zeping Niu <nnznk12@gmail.com>
  * @date 2017.5
  * @brief Header file for class AddAccountStrategy
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

namespace Ui {
class DetailWidget;
}

class DetailWidget : public QWidget
{
    Q_OBJECT
public slots:
	/**
	 * @brief consult this function is called iff the bill list needs to be refeshed
	 */
	void consult();
    void plot();
	/**
	 * @brief removeBill
	 * @param billId the id of bill to be removed
	 */
	void removeBill(ID billId);
public:
	explicit DetailWidget(QWidget *parent, UserManager *_userman);
    ~DetailWidget();
	/**
	 * @brief fillData
	 * @param bills the sorted bill to be filled into bill list widget
	 */
    void fillData(const QVector<Bill>& bills);
private:
    Ui::DetailWidget *ui;
    UserManager *userman;
};

#endif // DETAILWIDGET_H
