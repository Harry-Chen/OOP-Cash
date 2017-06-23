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
  * @file changebillwidget.h
  * @author Zeping Niu <nnznk12@gmail.com>
  * @date 2017.5
  * @brief Header file for class ChangeBillWidget
  */


#ifndef CHANGEBILLWIDGET_H
#define CHANGEBILLWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QMessageBox>
#include <QCalendarWidget>
#include <QRadioButton>

#include "dao/usermanager.h"
#include "dao/categorymanager.h"
#include "dao/accountmanager.h"
#include "dao/billmanager.h"
#include "dao/currencymanager.h"
#include "dao/itemmanager.h"
#include "util/itemsearcher.h"
#include "edititemwidgetfactory.h"
#include "calendardialog.h"

namespace Ui {
class ChangeBillWidget;
}

/**
 * @brief The abstract ui class to create and modify bill
 */
class ChangeBillWidget : public QWidget
{
	Q_OBJECT

public:
	/**
	 * @brief ChangeBillWidget Constructor
	 * @param parent the parent component
	 */
	explicit ChangeBillWidget(QWidget *parent = 0);
	/**
	 * @brief initialize the specific content got by UserManager
	 * @param userman the pointer of UserManager
	 */
	void init(UserManager* userman);
	~ChangeBillWidget();
public:
	/**
	 * @brief the method to get data from ui and add bill to sqlite
	 */
	virtual void addBill() = 0;
protected:
	Ui::ChangeBillWidget *ui;
	UserManager* _userman;
	EditItemWidget* _w;
	CalendarDialog* calendar;
	void clearWidget();
	virtual void setLabelNames() = 0; //QString strLabel1, QString strLabel2, QString strAmountLabel
	virtual void setCombobox1() = 0;
	virtual void setCombobox2() = 0;
	virtual void setCombobox3() = 0;
	void setCurrencyCombobox();
	QLabel* getLabel1();
	QLabel* getLabel2();
	QLabel* getLabel3();
	QLabel* getAmountLabel();
	QLabel* getLoanNameLabel();
	QRadioButton* getCostBtn();
	QRadioButton* getEarnBtn();
	QRadioButton* getTransferBtn();
	QLineEdit* getTimeLineEdit();
	QLineEdit* getMoneyLineEdit();
	QTextEdit* getNoteTextEdit();
	QComboBox* getCombobox1();
	QComboBox* getCombobox2();
	QComboBox* getCombobox3();
	QComboBox* getCurrencyCombobox();

public slots:
	/**
	 * @brief refresh the ui when status of the radio button changed
	 */
    void refresh();

private slots:
	void on_savebtn_clicked();
	void on_newCatebtn_clicked();
	void on_editCatebtn_clicked();
	void on_newCurrbtn_clicked();
	void on_editCurrbtn_clicked();
	void on_newAccbtn_clicked();
	void on_editAccbtn_clicked();
	void setDateByCalendar();
	void on_btnCalendar_clicked();
};

#endif // CHANGEBILLWIDGET_H
