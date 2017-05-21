#ifndef CHANGEBILLWIDGET_H
#define CHANGEBILLWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include "dao/usermanager.h"
#include "dao/categorymanager.h"
#include "dao/accountmanager.h"
#include "dao/billmanager.h"
#include "dao/currencymanager.h"
#include "dao/itemmanager.h"

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
public slots:
	virtual void addBill() = 0;
protected:
	Ui::ChangeBillWidget *ui;
	UserManager* _userman; // 不是自己分配的就不释放
	virtual void setLabelNames() = 0; //QString strLabel1, QString strLabel2, QString strAmountLabel
	virtual void setCombobox1() = 0;
	virtual void setCombobox2() = 0;
	void setCurrencyCombobox();
	QLabel* getLabel1();
	QLabel* getLabel2();
	QLabel* getLabel3();
	QLabel* getLoanNameLabel();
	QLineEdit* getLoanNameLineEdit();
	QLineEdit* getTimeLineEdit();
	QLineEdit* getAmountLineEdit();
	QTextEdit* getNoteTextEdit();
	QComboBox* getCombobox1();
	QComboBox* getCombobox2();
	QComboBox* getCurrencyCombobox();
protected:
	//静态方法, 只需要ItemManager管理的类有name字段即可
	template<typename T>
	static void getNameList(ItemManager<T>* man, QStringList& result)
	{
		//从manager中得到stringlist, 将具体getAllItem采用容器类型这一变化隔离出来
		auto itemMap = man->getAllItems(); //模板使得这一方法可以支持T中有name字段的全部情况
		//在没有name字段时会编译错误
		for(auto iter = itemMap.constBegin(); iter != itemMap.constEnd(); ++iter) {
			result << iter.value().name;
		}
	}

};

#endif // CHANGEBILLWIDGET_H
