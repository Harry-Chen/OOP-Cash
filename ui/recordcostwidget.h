#ifndef RECORDCOSTWIDGET_H
#define RECORDCOSTWIDGET_H

#include "changebillwidget.h"

class RecordCostWidget : public ChangeBillWidget
{
	Q_OBJECT

public:
    RecordCostWidget(QWidget *parent);
public slots:
	virtual void addBill();
protected:
	virtual void setLabelNames(); //QString strLabel1, QString strLabel2, QString strAmountLabel
	virtual void setCombobox1();
	virtual void setCombobox2();
};

#endif // RECORDCOSTWIDGET_H
