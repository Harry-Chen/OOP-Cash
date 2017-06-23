/**
 * Copyright 2017 OOP-Cash Team

 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file   edititemwidget.cpp
 * @author Zeping Niu <nnznk12@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class EditItemWidget
 */


#include "applyChangeStrategy/applychangestrategy.h"

#include "edititemwidget.h"
#include "ui_edititemwidget.h"


EditItemWidget::EditItemWidget(UserManager* userman, QWidget *parent) :
	_userman(userman),
	QDialog(parent),
	ui(new Ui::editItemWidget)
{
	ui->setupUi(this);
}

EditItemWidget::~EditItemWidget()
{
	delete ui;
}

QString EditItemWidget::getLabelText(int index)
{
	return (*(getlabelVector()))[index]->text();
}

QString EditItemWidget::getLineEditText1()
{
	return ui->lineEdit2->text();
}

QString EditItemWidget::getLineEditText2()
{
	return ui->lineEdit3->text();
}

QString EditItemWidget::getComboboxText()
{
	return ui->currComboBox->currentText();
}

EditItemWidget* EditItemWidget::setLabelName(QVector<QLabel*>& labelVector, \
											 const QStringList& namelist, \
											 const QVector<bool>& visiblelist)
{
	for(int i = 0; i < labelVector.size(); ++i) {
		(labelVector[i])->setText(namelist[i]);
		(labelVector[i])->setVisible(visiblelist[i]);
	}
	return this;
}

EditItemWidget* EditItemWidget::setLineEdit2(const QString& defaultText, bool visible)
{
	ui->lineEdit2->setText(defaultText);
	ui->lineEdit2->setVisible(visible);
	return this;
}

EditItemWidget* EditItemWidget::setLineEdit3(const QString& defaultText, bool visible)
{
	ui->lineEdit3->setText(defaultText);
	ui->lineEdit3->setVisible(visible);
	return this;
}

EditItemWidget* EditItemWidget::setCurrencyComboBox(bool visible)
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

EditItemWidget* EditItemWidget::setDeleteBtn(bool enabled)
{
	ui->deletebtn->setEnabled(enabled);
	return this;
}

EditItemWidget* EditItemWidget::setConformBtn(bool enabled)
{
	ui->conformbtn->setEnabled(enabled);
	return this;
}

EditItemWidget* EditItemWidget::setCancelBtn(bool enabled)
{
	ui->cancelbtn->setEnabled(enabled);
	return this;
}

EditItemWidget* EditItemWidget::setApplyChangeStrategy(ApplyChangeStrategy* _apply)
{
	apply = _apply;
	return this;
}

QVector<QLabel*>* EditItemWidget::getlabelVector()
{
	 auto labelVector = new QVector<QLabel*>;
	 labelVector->push_back(ui->label11);
	 labelVector->push_back(ui->label12);
	 labelVector->push_back(ui->label2);
	 labelVector->push_back(ui->label3);
	 return labelVector;
}



void EditItemWidget::on_deletebtn_clicked()
{
    if(QMessageBox::Yes == QMessageBox::question(this, QObject::tr("注意!"), \
                                                 QObject::tr("删除此条目会导致相关账单被连带删除, 是否继续?"), \
												 QMessageBox::Yes|QMessageBox::No, \
												 QMessageBox::Yes))
	{
		bool success = apply->applyDelete();
		emit modified();
		if(success) {
            QMessageBox::information(this, "", QObject::tr("成功删除条目"));
		} else {
            QMessageBox::information(this, "", QObject::tr("发生了一些奇怪的事情, 删除失败"));
		}
	}
	this->close();
}

void EditItemWidget::on_conformbtn_clicked()
{
	bool success = apply->applyChange();
	if(success) {
		emit modified();
        QMessageBox::information(this, "", QObject::tr("编辑成功"));
		this->close();
	}else {
        QMessageBox::information(this, "", QObject::tr("此条目已经存在, 添加失败"));
	}
}

void EditItemWidget::on_cancelbtn_clicked()
{
	this->close();
}
