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
 * @file   billdetailwidget.cpp
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Implementation file of class BillDetailWidget
 */

#include "billdetailwidget.h"
#include "ui_billdetailwidget.h"

BillDetailWidget::BillDetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillDetailWidget)
{
    ui->setupUi(this);
}

void BillDetailWidget::fillData(const Bill &bill, const QMap<ID, Account>& allAccounts, const QMap<ID, Category>& allCategories)
{
    QString quantity, account, category;
    quantity = QString::number(((double)bill.quantity)/100);
    if(bill.from == -1){
        account = allAccounts[bill.to].name;
    }
    else if(bill.to == -1){
        quantity.prepend('-');
        account = allAccounts[bill.from].name;
    }
    else{
        account = allAccounts[bill.from].name + "->" + allAccounts[bill.to].name;
    }
    quantity.prepend(QObject::tr("￥")).prepend(QObject::tr("金额\n"));
    category = allCategories[bill.category].name;
    ui->labelQuantity->setText(quantity);
    ui->labelNote->setText(QObject::tr("关键字\n") + bill.note);
    ui->labelDate->setText(bill.date.toString(QObject::tr("yyyy-MM-dd")).prepend(QObject::tr("日期\n")));
    ui->labelAccount->setText(account.prepend(QObject::tr("帐户\n")));
    ui->labelCategory->setText(category.prepend(QObject::tr("类别\n")));
}

BillDetailWidget::~BillDetailWidget()
{
    delete ui;
}
