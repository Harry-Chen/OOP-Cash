#include "querywidget.h"
#include "ui_querywidget.h"
#include "util/database_helper.h"
#include "ui/dateeditcalendar.h"
#include <QStringList>
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
    pQuery = &((Query::newQuery(DatabaseHelper::getDb())).addCreatorId(pUserManager->getLoggedInUid()));

    pQuery->setDateRange(ui->timeFrom->date(), ui->timeTo->date());

   // std::cout << ui->timeFrom->date().toString("dd.MM.yyyy").toStdString() << std::endl;
   // std::cout << ui->timeTo->date().toString("dd.MM.yyyy").toStdString() << std::endl;

    if (ui->finished->currentText() != "both")
    {
        if(ui->finished->currentText() == "finished") pQuery->setFinished(true);
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
        QMessageBox::information(0,"","无相应账单\n");
        logging::error("Empty! \n");
        return;
    }
    if(ui->selectField->currentIndex() == 0)
    {
        QMessageBox::information(0,"","请先选择查询类型\n");
        return;
    }
    for(int i = 0; i < ids.size(); ++i)
        nameMap.insert(ids[i], names[i]);

    //ProcessorFactory * pProcessorFactory = new ProcessorFactory;
    PlotSystem * pPlotSystem = new BillsPlotSystem;
    pProcessor = pPlotSystem ->createProcessor(bills, nameMap, static_cast<Plot::Time> (ui->timeType->currentIndex()),static_cast<Plot::Field> (ui->selectField->currentIndex()));
    if(!pProcessor->ProcessAll()) logging::error("fail to process\n");
    else setupPlot();/*plot*/
}


void QueryWidget::setupPlot()
{
    //GraphDock * GraphDockPtr = new GraphDock(pProcessor);
    //GraphDockPtr->show();
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
