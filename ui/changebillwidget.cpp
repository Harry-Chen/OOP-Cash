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
 * @file   changebillwidget.cpp
 * @author Zeping Niu <nnznk12@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class ChangeBillWidget
 */


#include "changebillwidget.h"
#include "ui_changebillwidget.h"
#include "util/constants.h"

ChangeBillWidget::ChangeBillWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChangeBillWidget)
{
	_w = nullptr;
	_userman = nullptr;
	ui->setupUi(this);

	/* use Validiator to make sure the input string is number format*/
	ui->lineEditAmount->setValidator(new QDoubleValidator(ui->lineEditAmount));
	calendar = new CalendarDialog(this);
	/* once receiving the seletedDateChanged signal, set the content on line edit */
	connect(calendar, SIGNAL(seletedDateChanged()), this, SLOT(setDateByCalendar()));
	ui->costBtn->setVisible(false);
	ui->earnBtn->setVisible(false);
}

void ChangeBillWidget::init(UserManager* userman) {
	//初始化userman;
	_userman = userman;
	//之后利用虚函数延迟初始化可变内容到子类
	setLabelNames();
	setCombobox1();
	setCombobox2();
	setCombobox3();
	setCurrencyCombobox();
    getTimeLineEdit()->setText(QDate().currentDate().toString(QObject::tr("yyyy-MM-dd")));
	otherSettings();
}

ChangeBillWidget::~ChangeBillWidget()
{
	delete ui;
	_userman = nullptr;
}

void ChangeBillWidget::refresh()
{
	setCombobox1();
	setCombobox2();
	setCombobox3();
	setCurrencyCombobox();
}

void ChangeBillWidget::setDateByCalendar()
{
	QDate date = calendar->getSelectedDate();
	getTimeLineEdit()->setText(date.toString("yyyy-MM-dd"));
}

void ChangeBillWidget::clearWidget()
{
	getMoneyLineEdit()->clear();
	getNoteTextEdit()->clear();
}

void ChangeBillWidget::setCurrencyCombobox()
{
	CurrencyManager* currman = new CurrencyManager(_userman);
	QStringList currList;
	ItemSearcher::instance()->getNameList(currman, currList);
	getCurrencyCombobox()->clear();
	getCurrencyCombobox()->addItems(currList);
}

QLabel* ChangeBillWidget::getLabel1()
{
	return ui->label1;
}

QLabel* ChangeBillWidget::getLabel2()
{
	return ui->label2;
}

QLabel*ChangeBillWidget::getLabel3()
{
	return ui->label3;
}

QLabel* ChangeBillWidget::getAmountLabel()
{
	return ui->labelAmount;
}

QRadioButton*ChangeBillWidget::getCostBtn()
{
	return ui->costBtn;
}

QRadioButton*ChangeBillWidget::getEarnBtn()
{
	return ui->earnBtn;
}

QRadioButton*ChangeBillWidget::getTransferBtn()
{
	return ui->tranferBtn;
}

QLineEdit*ChangeBillWidget::getTimeLineEdit()
{
	return ui->lineEditTime;
}

QLineEdit*ChangeBillWidget::getMoneyLineEdit()
{
	return ui->lineEditAmount;
}

QTextEdit*ChangeBillWidget::getNoteTextEdit()
{
	return ui->textEdit;
}

QComboBox* ChangeBillWidget::getCombobox1()
{
	return ui->combo1;
}

QComboBox* ChangeBillWidget::getCombobox2()
{
	return ui->combo2;
}

QComboBox*ChangeBillWidget::getCombobox3()
{
	return ui->combo3;
}

QComboBox* ChangeBillWidget::getCurrencyCombobox()
{
	return ui->comboCurrency;
}

void ChangeBillWidget::on_savebtn_clicked()
{
	addAndEditBill();
}

void ChangeBillWidget::on_newCatebtn_clicked()
{
	_w = EditItemWidgetFactory(_userman).getNewCategoryWidget(this);
	connect(_w, SIGNAL(modified()), this, SLOT(refresh()));
	_w->exec();
}

void ChangeBillWidget::on_editCatebtn_clicked()
{
	_w = EditItemWidgetFactory(_userman).getEditCategoryWidget(this, getCombobox1()->currentText());
	connect(_w, SIGNAL(modified()), this, SLOT(refresh()));
	_w->exec();
}

void ChangeBillWidget::on_newCurrbtn_clicked()
{
	_w = EditItemWidgetFactory(_userman).getNewCurrencyWidget(this);
	connect(_w, SIGNAL(modified()), this, SLOT(refresh()));
	_w->exec();
}

void ChangeBillWidget::on_editCurrbtn_clicked()
{
	_w = EditItemWidgetFactory(_userman).getEditCurrencyWidget(this, getCurrencyCombobox()->currentText());
	connect(_w, SIGNAL(modified()), this, SLOT(refresh()));
	_w->exec();
}

void ChangeBillWidget::on_newAccbtn_clicked()
{
	_w = EditItemWidgetFactory(_userman).getNewAccountWidget(this);
	connect(_w, SIGNAL(modified()), this, SLOT(refresh()));
	_w->exec();
}

void ChangeBillWidget::on_editAccbtn_clicked()
{
	_w = EditItemWidgetFactory(_userman).getEditAccountWidget(this, getCombobox2()->currentText());
	connect(_w, SIGNAL(modified()), this, SLOT(refresh()));
	_w->exec();
}

void ChangeBillWidget::on_btnCalendar_clicked()
{
	calendar->setVisible(true);
}
