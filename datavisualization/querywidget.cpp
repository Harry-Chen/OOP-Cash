#include "querywidget.h"
#include "ui_querywidget.h"
#include "util/database_helper.h"
#include <QStringList>

QueryWidget::QueryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QueryWidget)
{
    ui->setupUi(this);
    connect(ui->selectField, SIGNAL(currentIndexChanged(int)), this, SLOT(getField(int)));
    connect(ui->Do, SIGNAL(released()), this, SLOT(Do()));
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
//    case byCreator:
//    {
//        const auto& map3 = pUserManager->getAllItems();
//        foreach(auto temp, map3)
//            names.push_back(temp.nickname);
//        ids = map3.keys();
//        break;
//    }
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

    //pQuery->setDateRange(ui->timeFrom->date(), ui->timeTo->date());

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
        for(int i = 0; i < isSelected.size(); ++i)
            if(isSelected[i]) pQuery->addCategoryId(ids[i]);
        break;
    }
    case byAccountFrom:
    {
        for(int i = 0; i < isSelected.size(); ++i)
            if(isSelected[i]) pQuery->addFromAccountId(ids[i]);
        break;
    }
    case byAccountTo:
    {
        for(int i = 0; i < isSelected.size(); ++i)
            if(isSelected[i]) pQuery->addToAccountId(ids[i]);
        break;
    }
//    case byCreator:
//    {
//        for(int i = 0; i < isSelected.size(); ++i)
//            if(isSelected[i]) pQuery->addCreatorId(ids[i]);
//        break;
//    }
    default:
    {
        logging::error("Wrong ShowType!\n");
        break;
    }

    }
    const QVector<Bill> &bills = pQuery->doQuery();
    if(!bills.size())
    {
        logging::error("Empty! \n");
        return;
    }

    for(int i = 0; i < ids.size(); ++i)
        nameMap.insert(ids[i], names[i]);

    ProcessorFactory * pProcessorFactory = new ProcessorFactory;
    pProcessor = pProcessorFactory->creatProcessor(ui->timeType->currentIndex(), ui->selectField->currentIndex(), bills, nameMap);
    if(!pProcessor->processAll()) logging::error("fail to process\n");
    else setupPlot();/*plot*/
}


void QueryWidget::setupPlot()
{
    GraphDock * GraphDockPtr = new GraphDock(pProcessor);
    GraphDockPtr->show();
}
