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
  * @file recordcostearnwidget.h
  * @author Zeping Niu <nnznk12@gmail.com>
  * @date 2017.5
  * @brief Header file for class RecordCostEarnWidget
  */


#ifndef RECORDCOSTWIDGET_H
#define RECORDCOSTWIDGET_H

#include <QRadioButton>

#include "changebillwidget.h"

/**
 * @brief The RecordCostEarnWidget class
 */
class RecordCostEarnWidget : public ChangeBillWidget
{
	Q_OBJECT

public:
	/**
	 * @brief RecordCostEarnWidget
	 * @param parent
	 */
	RecordCostEarnWidget(QWidget* parent = nullptr, Bill* oldBill = nullptr);
public slots:
	/**
	 * @brief add or eidt Bill in sqlite
	 */
	virtual void addAndEditBill();
	void setIsCostTrue();
	void setIsCostFalse();
	void setIsTransfer();
protected:
	/*
	 * set names and contents of the ui components
	 */
	virtual void setLabelNames();
	virtual void setCombobox1();
	virtual void setCombobox2();
	virtual void setCombobox3();
private:
	bool isCost;
	bool isTransfer;
	void setOldBillChoice();
	void setCostLabelNames();
	void setEarnLabelNames();
	void setTransferLabelNames();
};

#endif // RECORDCOSTWIDGET_H
