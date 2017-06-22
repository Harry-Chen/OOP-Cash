#ifndef DETAILWIDGET_H
#define DETAILWIDGET_H

#include <QWidget>
#include <QVector>

#include "dao/usermanager.h"
#include "model/bill.h"
#include "plot/balanceplotsystem.h"

namespace Ui {
class DetailWidget;
}

class DetailWidget : public QWidget
{
    Q_OBJECT
public slots:
	void consult();
    void plot();

public:
    explicit DetailWidget(QWidget *parent, UserManager *_userman);
    ~DetailWidget();
    void fillData(const QVector<Bill>& bills);
private:
    Ui::DetailWidget *ui;
    UserManager *userman;
};

#endif // DETAILWIDGET_H
