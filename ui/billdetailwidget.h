#ifndef BILLDETAILWIDGET_H
#define BILLDETAILWIDGET_H

#include <QWidget>
#include "model/bill.h"
#include "dao/usermanager.h"

namespace Ui {
class BillDetailWidget;
}

class BillDetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BillDetailWidget(QWidget *parent = 0);
    void fillData(const Bill& bill, UserManager *userman);
    ~BillDetailWidget();

private:
    Ui::BillDetailWidget *ui;
};

#endif // BILLDETAILWIDGET_H
