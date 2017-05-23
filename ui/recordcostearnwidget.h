#ifndef RECORDCOSTWIDGET_H
#define RECORDCOSTWIDGET_H

#include "changebillwidget.h"
#include <QRadioButton>
#include <QPixmap>

class RecordCostEarnWidget : public ChangeBillWidget
{
	Q_OBJECT

public:
	RecordCostEarnWidget(QWidget* parent = nullptr);
public slots:
	virtual void addBill();
	void setIsCostTrue();
	void setIsCostFalse();
	void setIsTransfer();
protected:
	virtual void setLabelNames(); //QString strLabel1, QString strLabel2, QString strAmountLabel
	virtual void setCombobox1();
	virtual void setCombobox2();
	virtual void setCombobox3();
private:
	QPixmap* costIcon;
	QPixmap* earnIcon;
	bool isCost;
	bool isTransfer;
	void setCostLabelNames();
	void setEarnLabelNames();
	void setTransferLabelNames();
};

#endif // RECORDCOSTWIDGET_H
