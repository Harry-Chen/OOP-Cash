#include "detailwidget.h"
#include "ui_detailwidget.h"
#include "ui/billdetailwidget.h"
#include "dao/query.h"
#include "util/database_helper.h"
#include "process/balanceprocessor.h"
#include "datavisualization/graphdock.h"

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
        ui->listBills->setItemWidget(item, detail);
    }
	ui->listBills->setVisible(true);
}

void DetailWidget::consult()
{
	this->setCursor(Qt::WaitCursor);
	fillData(Query::newQuery(DatabaseHelper::getDb())
			 .addCreatorId(userman->getLoggedInUid())
			 .setDateRange(ui->timeFrom->date(), ui->timeTo->date())
			 .doQuery());
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
