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
 * @file   querywidget.cpp
 * @author 牛辰昊
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Implementation file of class QueryWidget
 */

#include <QStringList>

#include "querywidget.h"
#include "ui_querywidget.h"
#include "util/database_helper.h"
#include "ui/calendardialog.h"

QueryWidget::QueryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryWidget)
{
    ui->setupUi(this);
    calendarFrom = new CalendarDialog(this);
    calendarTo = new CalendarDialog(this);
    connect(ui->selectField, SIGNAL(currentIndexChanged(int)), this, SLOT(getField(int)));
    connect(ui->Do, SIGNAL(clicked(bool)), this, SLOT(Do()));
    connect(ui->btnCalendarFrom,SIGNAL(clicked(bool)),this,SLOT(setupCalendarFrom()));
    connect(ui->btnCalendarTo,SIGNAL(clicked(bool)),this,SLOT(setupCalendarTo()));
    connect(calendarFrom, SIGNAL(seletedDateChanged()),this, SLOT(setDateFrom()));
    connect(calendarTo, SIGNAL(seletedDateChanged()),this, SLOT(setDateTo()));
    ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    init();
}

void QueryWidget::init()
{
    names.clear();
    ids.clear();
    ui->listWidget->clear();
    ui->timeFrom->setDateTime(QDateTime::fromTime_t(0));
    ui->timeTo->setDateTime(QDateTime::currentDateTime());
}

void QueryWidget::setUserman(UserManager * _pUserManager)
{
    pUserManager = _pUserManager;
}


QueryWidget::~QueryWidget()
{
    delete ui;
}

void QueryWidget::getField(int _field)
{
    field = _field;
    names.clear();
    ids.clear();
    ui->listWidget->clear();
    switch (field)
    {
    case byCategory:
    {
        auto *newCategoryManager= new CategoryManager(pUserManager);
        const auto& map1 = newCategoryManager->getAllItems();
        foreach(auto temp, map1)
            names.push_back(temp.name);
        ids = map1.keys();
        delete newCategoryManager;
        break;
    }
    case byAccountFrom:
    case byAccountTo:
    {
        auto *newAccountManager= new AccountManager(pUserManager);
        const auto& map2 = newAccountManager->getAllItems();
        foreach(auto temp, map2)
            names.push_back(temp.name);
        ids = map2.keys();
        delete newAccountManager;
        break;
    }
    default:
    {
        logging::error("Wrong ShowType!\n");
        break;
    }
    }

    ui->listWidget->addItems(QStringList(names));
}

void QueryWidget::Do()
{
    const int FINISHED_INDEX_BOTH = 0;
    const int FINISHED_INDEX_FINISHED = 1;
    const int FINISHED_INDEX_UNFINISHED = 2;
    pQuery = &((Query::newQuery(DatabaseHelper::getDb())).addCreatorId(pUserManager->getLoggedInUid()));
    pQuery->setDateRange(ui->timeFrom->date(), ui->timeTo->date());
    if (ui->finished->currentIndex() != FINISHED_INDEX_BOTH)
    {
        if(ui->finished->currentIndex() == FINISHED_INDEX_FINISHED) pQuery->setFinished(true);
        else pQuery->setFinished(false);
    }
    if (ui->keyWord->isModified())
        pQuery->setKeyword(ui->keyWord->text());

    isSelected.clear();
    for(int i = 0; i < ids.size(); ++i)
        isSelected.push_back(ui->listWidget->item(i)->isSelected());
    switch (field)
    {
    case byCategory:
    {
        for(int i = 0; i < (int)isSelected.size(); ++i)
            if(isSelected[i]) pQuery->addCategoryId(ids[i]);
        break;
    }
    case byAccountFrom:
    {
        for(int i = 0; i < (int)isSelected.size(); ++i)
            if(isSelected[i]) pQuery->addFromAccountId(ids[i]);
        break;
    }
    case byAccountTo:
    {
        for(int i = 0; i < (int)isSelected.size(); ++i)
            if(isSelected[i]) pQuery->addToAccountId(ids[i]);
        break;
    }
    default:
    {
        logging::error("Wrong ShowType!\n");
        break;
    }

    }
    const QVector<Bill> &bills = pQuery->doQuery();
    if(!bills.size())
    {
        QMessageBox::information(0,"",QObject::tr("无相应账单\n"));
        logging::error("Empty! \n");
        return;
    }
    if(ui->selectField->currentIndex() == 0)
    {
        QMessageBox::information(0,"",QObject::tr("请先选择查询类型\n"));
        return;
    }
    for(int i = 0; i < ids.size(); ++i)
        nameMap.insert(ids[i], names[i]);

    PlotSystem * pPlotSystem = new BillsPlotSystem;
    Processor * pProcessor = pPlotSystem ->createProcessor(bills, nameMap, static_cast<Plot::Time> (ui->timeType->currentIndex()),static_cast<Plot::Field> (ui->selectField->currentIndex()));
    if(!pProcessor->ProcessAll()) logging::error("fail to process\n");
    else
    {
        Plotter * pPlotter = pPlotSystem->createPlotter(pProcessor->GetFieldnames(), pProcessor->GetDates(), pProcessor->GetValues());
        GraphDock * GraphDockPtr = new GraphDock(pPlotter);
        GraphDockPtr->show();
    }
    delete pPlotSystem;
    delete pProcessor;
}


void QueryWidget::setupCalendarFrom()
{
    calendarFrom->setVisible(true);
}

void QueryWidget::setupCalendarTo()
{
    calendarTo->setVisible(true);
}

void QueryWidget::setDateFrom()
{
    ui->timeFrom->setDate(calendarFrom->getSelectedDate());
}

void QueryWidget::setDateTo()
{
    ui->timeTo->setDate(calendarTo->getSelectedDate());
}
