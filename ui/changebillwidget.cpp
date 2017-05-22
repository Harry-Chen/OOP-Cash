#include "changebillwidget.h"
#include "ui_changebillwidget.h"
#include "util/constants.h"

ChangeBillWidget::ChangeBillWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChangeBillWidget)
{
	_userman = nullptr;
	ui->setupUi(this);
	ui->lineEditAmount->setValidator(new QDoubleValidator(ui->lineEditAmount));
}

void ChangeBillWidget::init(UserManager* userman) {
	//初始化userman;
	_userman = userman;
	//之后利用虚函数延迟初始化到子类
	setLabelNames();
	setCombobox1();
	setCombobox2();
	setCurrencyCombobox();
	getLoanNameLabel()->setVisible(false);
	getLoanNameLineEdit()->setVisible(false);
}

ChangeBillWidget::~ChangeBillWidget()
{
	delete ui;
	_userman = nullptr;
}

void ChangeBillWidget::setCurrencyCombobox()
{
	CurrencyManager* currman = new CurrencyManager(_userman);
	QStringList currList;
	ItemSearcher::instance()->getNameList(currman, currList);
	getCurrencyCombobox()->clear();
	getCurrencyCombobox()->addItems(currList);
}

QLabel* ChangeBillWidget::getLabel1()
{
	return ui->label1;
}

QLabel* ChangeBillWidget::getLabel2()
{
	return ui->label2;
}

QLabel* ChangeBillWidget::getLabel3()
{
	return ui->labelAmount;
}

QLabel*ChangeBillWidget::getLoanNameLabel()
{
	return ui->labelLoadName;
}

QLineEdit*ChangeBillWidget::getLoanNameLineEdit()
{
	return ui->lineEditLoanName;
}

QLineEdit*ChangeBillWidget::getTimeLineEdit()
{
	return ui->lineEditTime;
}

QLineEdit*ChangeBillWidget::getMoneyLineEdit()
{
	return ui->lineEditAmount;
}

QTextEdit*ChangeBillWidget::getNoteTextEdit()
{
	return ui->textEdit;
}

QComboBox* ChangeBillWidget::getCombobox1()
{
	return ui->combo1;
}

QComboBox* ChangeBillWidget::getCombobox2()
{
	return ui->combo2;
}

QComboBox* ChangeBillWidget::getCurrencyCombobox()
{
	return ui->comboCurrency;
}

void ChangeBillWidget::on_savebtn_released()
{
	addBill();
}
