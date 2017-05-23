#include "edititemwidget.h"
#include "ui_edititemwidget.h"
#include "applyChangeStrategy/applychangestrategy.h"

editItemWidget::editItemWidget(UserManager* userman, QWidget *parent) :
	_userman(userman),
	QDialog(parent),
	ui(new Ui::editItemWidget)
{
	ui->setupUi(this);
}

editItemWidget::~editItemWidget()
{
	delete ui;
}

QString editItemWidget::getLabelText(int index)
{
	return (*(getlabelVector()))[index]->text();
}

QString editItemWidget::getLineEditText1()
{
	return ui->lineEdit2->text();
}

QString editItemWidget::getLineEditText2()
{
	return ui->lineEdit3->text();
}

QString editItemWidget::getComboboxText()
{
	return ui->currComboBox->currentText();
}

editItemWidget* editItemWidget::setLabelName(QVector<QLabel*>& labelVector, \
											 const QStringList& namelist, \
											 const QVector<bool>& visiblelist)
{
	for(int i = 0; i < labelVector.size(); ++i) {
		(labelVector[i])->setText(namelist[i]);
		(labelVector[i])->setVisible(visiblelist[i]);
	}
	return this;
}

editItemWidget* editItemWidget::setLineEdit2(const QString& defaultText, bool visible)
{
	ui->lineEdit2->setText(defaultText);
	ui->lineEdit2->setVisible(visible);
	return this;
}

editItemWidget* editItemWidget::setLineEdit3(const QString& defaultText, bool visible)
{
	ui->lineEdit3->setText(defaultText);
	ui->lineEdit3->setVisible(visible);
	return this;
}

editItemWidget* editItemWidget::setCurrencyComboBox(bool visible)
{
	if(!visible) {
		ui->currComboBox->setVisible(visible);
		return this;
	}
	QStringList ans;
	auto currman = new CurrencyManager(_userman);
	ItemSearcher::instance()->getNameList(currman, ans);
	delete currman;
	ui->currComboBox->clear();
	ui->currComboBox->addItems(ans);
	return this;
}

editItemWidget* editItemWidget::setDeleteBtn(bool enabled)
{
	ui->deletebtn->setEnabled(enabled);
	return this;
}

editItemWidget* editItemWidget::setConformBtn(bool enabled)
{
	ui->conformbtn->setEnabled(enabled);
	return this;
}

editItemWidget* editItemWidget::setCancelBtn(bool enabled)
{
	ui->cancelbtn->setEnabled(enabled);
	return this;
}

editItemWidget* editItemWidget::setApplyChangeStrategy(applyChangeStrategy* _apply)
{
	apply = _apply;
	return this;
}

QVector<QLabel*>* editItemWidget::getlabelVector()
{
	 auto labelVector = new QVector<QLabel*>;
	 labelVector->push_back(ui->label11);
	 labelVector->push_back(ui->label12);
	 labelVector->push_back(ui->label2);
	 labelVector->push_back(ui->label3);
	 return labelVector;
}



void editItemWidget::on_deletebtn_clicked()
{
	apply->applyDelete();
	emit modified();
	this->close();
}

void editItemWidget::on_conformbtn_clicked()
{
	apply->applyChange();
	emit modified();
}
