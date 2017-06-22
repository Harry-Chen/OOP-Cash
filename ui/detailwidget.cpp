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
 * @file   detailwidget.cpp
 * @author ...
 * @author Zeping Niu <nnznk12@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class DetailWidget
 */


#include "ui/billdetailwidget.h"
#include "dao/query.h"
#include "util/database_helper.h"
#include "process/balanceprocessor.h"
#include "datavisualization/graphdock.h"

#include "detailwidget.h"
#include "ui_detailwidget.h"


DetailWidget::DetailWidget(QWidget *parent, UserManager *_userman) :
    QWidget(parent),
    ui(new Ui::DetailWidget),
    userman(_userman)
{
    ui->setupUi(this);
	//connect(ui->timeFrom,SIGNAL(editingFinished()),loadThread,SLOT(consult()));
	//connect(ui->timeTo,SIGNAL(editingFinished()),this,SLOT(consult()));
	connect(ui->refresh,SIGNAL(clicked(bool)),this,SLOT(consult()));
    connect(ui->plot,SIGNAL(clicked(bool)),this,SLOT(plot()));
    ui->timeFrom->setDateTime(QDateTime::fromTime_t(0));
    ui->timeTo->setDateTime(QDateTime::currentDateTime());
}

DetailWidget::~DetailWidget()
{
    delete ui;
}

void DetailWidget::fillData(const QVector<Bill> &bills)
{
	ui->listBills->setVisible(false);
	auto acc = new AccountManager(userman);
	auto cat = new CategoryManager(userman);
	const auto & allAccounts = acc->getAllItems();
	const auto & allCategories = cat->getAllItems();
    ui->listBills->clear();
    for(auto const & bill : bills){
        auto item = new QListWidgetItem(ui->listBills);
        item->setSizeHint(QSize(338,73));
        auto detail = new BillDetailWidget();
		detail->fillData(bill, allAccounts, allCategories);
		connect(detail, SIGNAL(delBillSignal(ID)),\
				this, SLOT(removeListWidgetItem(ID)));
        ui->listBills->setItemWidget(item, detail);
    }
	ui->listBills->setVisible(true);
}

void DetailWidget::consult()
{
	this->setCursor(Qt::WaitCursor);
	QVector<Bill>& billVector = Query::newQuery(DatabaseHelper::getDb())
			.addCreatorId(userman->getLoggedInUid())
			.setDateRange(ui->timeFrom->date(), ui->timeTo->date())
			.doQuery();
	class BillComparer {
	public:
		bool operator() (const Bill& b1, const Bill& b2) {
			return b2.date < b1.date;
		}
	};
	std::sort(billVector.begin(), billVector.end(), BillComparer());
	fillData(billVector);
	this->setCursor(Qt::ArrowCursor);
}

void DetailWidget::plot()
{
    QVector<Bill> bills = Query::newQuery(DatabaseHelper::getDb())
            .addCreatorId(userman->getLoggedInUid())
            .setDateRange(ui->timeFrom->date(), ui->timeTo->date())
            .doQuery();
    QMap <ID, QString> nameMap;
    nameMap.insert(userman->getLoggedInUid(), userman->getAllItems()[userman->getLoggedInUid()].nickname);
    PlotSystem * pPlotSystem = new BalancePlotSystem;
    Processor * pProcessor = pPlotSystem ->createProcessor(bills, nameMap);
    if(!pProcessor->ProcessAll()) logging::error("fail to process\n");
    else
    {
        Plotter * pPlotter = pPlotSystem->createPlotter(pProcessor->GetFieldnames(), pProcessor->GetDates(), pProcessor->GetValues());
        GraphDock * GraphDockPtr = new GraphDock(pPlotter);
        GraphDockPtr->show();
	}
}

void DetailWidget::removeListWidgetItem(ID billId)
{
	BillManager* billMan = new BillManager(userman);
	billMan->removeItemById(billId);
	delete billMan;
	consult();
}
