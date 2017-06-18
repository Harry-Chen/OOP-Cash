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
#include "dao/categorymanager.h"
#include "dao/accountmanager.h"

BillDetailWidget::BillDetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BillDetailWidget)
{
    ui->setupUi(this);
}

void BillDetailWidget::fillData(const Bill &bill, UserManager *userman)
{
    ID uid = userman->getLoggedInUid();
    auto acc = new AccountManager(userman);
    auto cat = new CategoryManager(userman);
    QString quantity, account, category;
    quantity = QString::number(((double)bill.quantity)/100);
    const auto & allAccounts = acc->getAllItems();
    const auto & allCategories = cat->getAllItems();
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
    quantity.prepend("￥").prepend("金额\n");
    category = allCategories[bill.category].name;
    ui->labelQuantity->setText(quantity);
    ui->labelNote->setText("关键字\n" + bill.note);
    ui->labelDate->setText(bill.date.toString("yyyy-MM-dd").prepend("日期\n"));
    ui->labelAccount->setText(account.prepend("帐户\n"));
    ui->labelCategory->setText(category.prepend("类别\n"));
}

BillDetailWidget::~BillDetailWidget()
{
    delete ui;
}
