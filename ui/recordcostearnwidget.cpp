﻿/**
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
 * @file   recordcostearnwidget.cpp
 * @author Zeping Niu <nnznk12@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class RecordCostEarnWidget
 */


#include "recordcostearnwidget.h"

RecordCostEarnWidget::RecordCostEarnWidget(QWidget* parent, Bill* oldBill): \
	ChangeBillWidget(parent)
{
	this->oldBill = oldBill;
	isCost = true;
	isTransfer = false;
	QRadioButton* cbtn = getCostBtn();
	QRadioButton* ebtn = getEarnBtn();
	QRadioButton* tbtn = getTransferBtn();
	cbtn->setVisible(true);
	ebtn->setVisible(true);
	tbtn->setVisible(true);
	connect(cbtn, SIGNAL(toggled(bool)), this, SLOT(setIsCostTrue()));
	connect(ebtn, SIGNAL(toggled(bool)), this, SLOT(setIsCostFalse()));
	connect(tbtn, SIGNAL(toggled(bool)), this, SLOT(setIsTransfer()));
}

void RecordCostEarnWidget::addAndEditBill()
{
	auto cateman = new CategoryManager(_userman);
	auto accman = new AccountManager(_userman);
	auto currman = new CurrencyManager(_userman);
	auto cate = ItemSearcher::instance()->getItemByName(cateman, getCombobox1()->currentText());
	auto acc = ItemSearcher::instance()->getItemByName(accman, getCombobox2()->currentText());
	Account accTo;
	if(isTransfer) {
		accTo = ItemSearcher::instance()->getItemByName(accman, getCombobox3()->currentText());
	} else {
		accTo.id = -1;
	}
	auto curr = ItemSearcher::instance()->getItemByName(currman, getCurrencyCombobox()->currentText());
	delete cateman;
	delete accman;
	delete currman;

	bool valid = true;
	QDate date = QDate::fromString(getTimeLineEdit()->text(), "yyyy-MM-dd");
	if(!date.isValid()) {
        QMessageBox::information(this, QObject::tr("错误"), QObject::tr("日期格式有误，应为：%1").arg("yyyy-MM-dd"));
		valid = false;
	}
	int money;
	if(getMoneyLineEdit()->hasAcceptableInput()) {
		money = int(getMoneyLineEdit()->text().toDouble() * 100);
	} else {
        QMessageBox::information(this, QObject::tr("错误"), QObject::tr("金额格式有误"));
		valid = false;
	}
	if(!valid) {
		return;
	} //else
	auto billman = new BillManager(_userman);
	auto newbill = new Bill(-1, -1, -1, _userman->getLoggedInUid(),\
						 cate.id, money, curr.id, QDateTime::currentDateTime(),\
						  true, date, getNoteTextEdit()->toPlainText());
	newbill->id = oldBill ? oldBill->id : -1;
	if(!isCost && !isTransfer) {
		newbill->to = acc.id;
	} else {
		newbill->from = acc.id;
		newbill->to = accTo.id;
	}
	if(newbill->id == -1) { // 添加账单
		if(billman->addItem(*newbill) == -1) {
			QMessageBox::information(this, QObject::tr("抱歉"), QObject::tr("保存账单时发生错误"));
		} else {
			QMessageBox::information(this, QObject::tr("提醒"), QObject::tr("账单保存成功"));
			clearWidget();
		}
	} else { // 修改账单
		if(billman->modifyItem(*newbill)) {
			QMessageBox::information(this, QObject::tr("提醒"), QObject::tr("账单修改成功"));
            dynamic_cast<QDialog*>(this->parent())->close();
		} else {
			QMessageBox::information(this, QObject::tr("抱歉"), QObject::tr("帐单修改失败"));
		}
	}
}

void RecordCostEarnWidget::setIsCostFalse()
{
	isCost = false;
	isTransfer = false;
	setLabelNames();
	setOldBillChoice();
}

void RecordCostEarnWidget::setIsTransfer()
{
	isTransfer = true;
	isCost = false;
	setLabelNames();
	setOldBillChoice();
}

void RecordCostEarnWidget::setIsCostTrue()
{
	isCost = true;
	isTransfer = false;
	setLabelNames();
	setOldBillChoice();
}

void RecordCostEarnWidget::setLabelNames()
{
	if(isTransfer) {
		setTransferLabelNames();
	} else if(isCost) {
		setCostLabelNames();
	} else {
		setEarnLabelNames();
	}
}

void RecordCostEarnWidget::setCombobox1()
{
	CategoryManager* cateman = new CategoryManager(_userman);
	QStringList cateList;
	ItemSearcher::instance()->getNameList(cateman, cateList); // 从manager直接得到StringList
	getCombobox1()->clear();
	getCombobox1()->addItems(cateList);
}

void RecordCostEarnWidget::setCombobox2()
{
	AccountManager* accman = new AccountManager(_userman);
	QStringList accList;
	ItemSearcher::instance()->getNameList(accman, accList);
	getCombobox2()->clear();
	getCombobox2()->addItems(accList);
}

void RecordCostEarnWidget::setCombobox3()
{
	AccountManager* accman = new AccountManager(_userman);
	QStringList accList;
	ItemSearcher::instance()->getNameList(accman, accList);
	getCombobox3()->clear();
	getCombobox3()->addItems(accList);
}

void RecordCostEarnWidget::otherSettings()
{
	if(!oldBill) return;
	auto accMan = new AccountManager(_userman);
	auto currMan = new CurrencyManager(_userman);
	auto cateMan = new CategoryManager(_userman);
	allAccount = accMan->getAllItems();
	allCurrency = currMan->getAllItems();
	allCategory = cateMan->getAllItems();
	if(oldBill->from != -1 && oldBill->to != -1) {
		getTransferBtn()->setChecked(true);
		setIsTransfer();
	} else if (oldBill->from != -1) {
		getCostBtn()->setChecked(true);
		setIsCostTrue();
	} else {
		getEarnBtn()->setChecked(true);
		setIsCostFalse();
	}
}

void RecordCostEarnWidget::setOldBillChoice()
{
	if(!oldBill) return;
	getCombobox1()->setCurrentText(allCategory[oldBill->category].name);
	getTimeLineEdit()->setText(oldBill->date.toString("yyyy-MM-dd"));
	getMoneyLineEdit()->setText(QString::number(oldBill->quantity*1.0/100, 'f', 2));
	getNoteTextEdit()->setText(oldBill->note);
	getCurrencyCombobox()->setCurrentText(allCurrency[oldBill->currency].name);
	if(isTransfer) {
		getCombobox2()->setCurrentText(allAccount[oldBill->from].name);
		getCombobox3()->setCurrentText(allAccount[oldBill->to].name);
	} else if(isCost) {
		getCombobox2()->setCurrentText(allAccount[oldBill->from].name);
	} else {
		getCombobox3()->setCurrentText(allAccount[oldBill->to].name);
	}
}

void RecordCostEarnWidget::setCostLabelNames()
{
    getLabel1()->setText(QObject::tr("账目分类"));
    getLabel2()->setText(QObject::tr("支出账户"));
    getAmountLabel()->setText(QObject::tr("支出金额"));
	getLabel3()->setVisible(false);
	getCombobox3()->setVisible(false);
}

void RecordCostEarnWidget::setEarnLabelNames()
{
    getLabel1()->setText(QObject::tr("账目分类"));
    getLabel2()->setText(QObject::tr("收入账户"));
    getAmountLabel()->setText(QObject::tr("收入金额"));
	getLabel3()->setVisible(false);
	getCombobox3()->setVisible(false);
}

void RecordCostEarnWidget::setTransferLabelNames()
{
    getLabel1()->setText(QObject::tr("账目分类"));
    getLabel2()->setText(QObject::tr("转出账户"));
    getLabel3()->setText(QObject::tr("转入账户"));
	getLabel3()->setVisible(true);
	getCombobox3()->setVisible(true);
    getAmountLabel()->setText(QObject::tr("转账金额"));
}
