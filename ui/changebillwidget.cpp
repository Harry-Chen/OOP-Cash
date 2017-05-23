#include "changebillwidget.h"
#include "ui_changebillwidget.h"
#include "util/constants.h"

ChangeBillWidget::ChangeBillWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChangeBillWidget)
{
	_w = nullptr;
	_userman = nullptr;
	ui->setupUi(this);
	ui->lineEditAmount->setValidator(new QDoubleValidator(ui->lineEditAmount));
	calendar = new CalendarDialog(this);
	connect(calendar, SIGNAL(seletedDateChanged()), this, SLOT(setDateByCalendar()));
	ui->costBtn->setVisible(false);
	ui->earnBtn->setVisible(false);
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
	getTimeLineEdit()->setText(QDate().currentDate().toString("yyyy-MM-dd"));
}

ChangeBillWidget::~ChangeBillWidget()
{
	delete ui;
	_userman = nullptr;
}

void ChangeBillWidget::refresh()
{
	setCombobox1();
	setCombobox2();
	setCurrencyCombobox();
}

void ChangeBillWidget::setDateByCalendar()
{
	QDate date = calendar->getSelectedDate();
	getTimeLineEdit()->setText(date.toString("yyyy-MM-dd"));
}

void ChangeBillWidget::clearWidget()
{
	getMoneyLineEdit()->clear();
	getNoteTextEdit()->clear();
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

void ChangeBillWidget::on_savebtn_clicked()
{
	addBill();
}

void ChangeBillWidget::on_newCatebtn_clicked()
{
	_w = editItemWidgetFactory(_userman).getNewCategoryWidget(this);
	connect(_w, SIGNAL(modified()), this, SLOT(refresh()));
	_w->exec();
}

void ChangeBillWidget::on_editCatebtn_clicked()
{
	_w = editItemWidgetFactory(_userman).getEditCategoryWidget(this, getCombobox1()->currentText());
	connect(_w, SIGNAL(modified()), this, SLOT(refresh()));
	_w->exec();
}

void ChangeBillWidget::on_newCurrbtn_clicked()
{
	_w = editItemWidgetFactory(_userman).getNewCurrencyWidget(this);
	connect(_w, SIGNAL(modified()), this, SLOT(refresh()));
	_w->exec();
}

void ChangeBillWidget::on_editCurrbtn_clicked()
{
	_w = editItemWidgetFactory(_userman).getEditCurrencyWidget(this, getCurrencyCombobox()->currentText());
	connect(_w, SIGNAL(modified()), this, SLOT(refresh()));
	_w->exec();
}

void ChangeBillWidget::on_newAccbtn_clicked()
{
	_w = editItemWidgetFactory(_userman).getNewAccountWidget(this);
	connect(_w, SIGNAL(modified()), this, SLOT(refresh()));
	_w->exec();
}

void ChangeBillWidget::on_editAccbtn_clicked()
{
	_w = editItemWidgetFactory(_userman).getEditAccountWidget(this, getCombobox2()->currentText());
	connect(_w, SIGNAL(modified()), this, SLOT(refresh()));
	_w->exec();
}

void ChangeBillWidget::on_btnCalendar_clicked()
{
	calendar->setVisible(true);
}
