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
}

void QueryWidget::setUserman(UserManager * _pUserManager)
{
    pUserManager = _pUserManager;
}


QueryWidget::~QueryWidget()
{
    delete ui;
}

void QueryWidget::getField(int field)
{
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
    case byCreator:
    {
        const auto& map3 = pUserManager->getAllItems();
        foreach(auto temp, map3)
            names.push_back(temp.nickname);
        ids = map3.keys();
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
    * pQuery = Query::newQuery(DatabaseHelper::getDb());
    pQuery->setDateRange(ui->timeFrom->date(), ui->timeTo->date());
    if (ui->finished->currentText() != "both")
    {
        if(ui->finished->currentText() == "finished") pQuery->setFinished(true);
        else pQuery->setFinished(false);
    }
    if (ui->keyWord->isModified())
        pQuery->setKeyword(ui->keyWord->text());


    ProcessorFactory * pProcessorFactory = new ProcessorFactory;
    pProcessor = pProcessorFactory->creatProcessor(ui->timeType->currentIndex(), ui->selectField->currentIndex(), pQuery);
    if(!pProcessor->processAll()) ;//error
    else ;/* plot */
}
