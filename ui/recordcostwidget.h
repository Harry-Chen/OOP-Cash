#ifndef RECORDCOSTWIDGET_H
#define RECORDCOSTWIDGET_H

#include "changebillwidget.h"
#include <QRadioButton>

class RecordCostWidget : public ChangeBillWidget
{
	Q_OBJECT

public:
	RecordCostWidget(QWidget* parent = nullptr);
public slots:
	virtual void addBill();
	void setIsCostTrue();
	void setIsCostFalse();
protected:
	virtual void setLabelNames(); //QString strLabel1, QString strLabel2, QString strAmountLabel
	virtual void setCombobox1();
	virtual void setCombobox2();
private:
	bool isCost;
	void setCostLabelNames();
	void setEarnLabelNames();
};

#endif // RECORDCOSTWIDGET_H
