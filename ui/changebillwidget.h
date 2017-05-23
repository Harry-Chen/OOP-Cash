#ifndef CHANGEBILLWIDGET_H
#define CHANGEBILLWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QMessageBox>
#include <QCalendarWidget>
#include <QRadioButton>
#include "dao/usermanager.h"
#include "dao/categorymanager.h"
#include "dao/accountmanager.h"
#include "dao/billmanager.h"
#include "dao/currencymanager.h"
#include "dao/itemmanager.h"
#include "util/itemsearcher.h"
#include "edititemwidgetfactory.h"
#include "calendardialog.h"

namespace Ui {
class ChangeBillWidget;
}

class ChangeBillWidget : public QWidget
{
	Q_OBJECT

public:
	explicit ChangeBillWidget(QWidget *parent = 0);
	void init(UserManager* userman);
	~ChangeBillWidget();
public:
	virtual void addBill() = 0;
protected:
	Ui::ChangeBillWidget *ui;
	UserManager* _userman; // 不是自己分配的就不释放
	editItemWidget* _w;
	CalendarDialog* calendar;
	void clearWidget();
	virtual void setLabelNames() = 0; //QString strLabel1, QString strLabel2, QString strAmountLabel
	virtual void setCombobox1() = 0;
	virtual void setCombobox2() = 0;
	virtual void setCombobox3() = 0;
	void setCurrencyCombobox();
	QLabel* getLabel1();
	QLabel* getLabel2();
	QLabel* getLabel3();
	QLabel* getAmountLabel();
	QLabel* getLoanNameLabel();
	QRadioButton* getCostBtn();
	QRadioButton* getEarnBtn();
	QRadioButton* getTransferBtn();
	QLineEdit* getTimeLineEdit();
	QLineEdit* getMoneyLineEdit();
	QTextEdit* getNoteTextEdit();
	QComboBox* getCombobox1();
	QComboBox* getCombobox2();
	QComboBox* getCombobox3();
	QComboBox* getCurrencyCombobox();

public slots:
    void refresh();

private slots:
	void on_savebtn_clicked();
	void on_newCatebtn_clicked();
	void on_editCatebtn_clicked();
	void on_newCurrbtn_clicked();
	void on_editCurrbtn_clicked();
	void on_newAccbtn_clicked();
	void on_editAccbtn_clicked();
	void setDateByCalendar();
	void on_btnCalendar_clicked();
};

#endif // CHANGEBILLWIDGET_H
