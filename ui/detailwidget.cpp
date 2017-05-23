#include "detailwidget.h"
#include "ui_detailwidget.h"
#include "ui/billdetailwidget.h"
#include "dao/query.h"
#include "util/database_helper.h"

DetailWidget::DetailWidget(QWidget *parent, UserManager *_userman) :
    QWidget(parent),
    ui(new Ui::DetailWidget),
    userman(_userman)
{
    ui->setupUi(this);
    //For test only
    fillData(Query::newQuery(DatabaseHelper::getDb())
             .addCreatorId(userman->getLoggedInUid()).doQuery());
}

DetailWidget::~DetailWidget()
{
    delete ui;
}

void DetailWidget::fillData(const QVector<Bill> &bills)
{
    ui->listBills->clear();
    for(auto const & bill : bills){
        auto item = new QListWidgetItem(ui->listBills);
        item->setSizeHint(QSize(338,73));
        auto detail = new BillDetailWidget();
        detail->fillData(bill, userman);
        ui->listBills->setItemWidget(item, detail);
    }
}
