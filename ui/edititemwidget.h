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
  * @file edititemwidget.h
  * @author Zeping Niu <nnznk12@gmail.com>
  * @date 2017.5
  * @brief Header file for class EditItemWidget
  */


#ifndef EDITITEMWIDGET_H
#define EDITITEMWIDGET_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>

#include "util/itemsearcher.h"

class ApplyChangeStrategy;

namespace Ui {
class editItemWidget;
}

class EditItemWidget : public QDialog
{
	Q_OBJECT

public:
	explicit EditItemWidget(UserManager* userman, QWidget *parent = 0);
	~EditItemWidget();
	QString getLabelText(int index);
	QString getLineEditText1();
	QString getLineEditText2();
	QString getComboboxText();
	QVector<QLabel*>* getlabelVector();
	EditItemWidget* setApplyChangeStrategy(ApplyChangeStrategy* _apply);
	EditItemWidget* setLabelName(QVector<QLabel*> & labelVector, const QStringList& namelist, const QVector<bool>& visiblelist);
	EditItemWidget* setLineEdit2(const QString&defaultText = "", bool visible = true);
	EditItemWidget* setLineEdit3(const QString&defaultText = "", bool visible = true);
	EditItemWidget* setCurrencyComboBox(bool visible = true);
	EditItemWidget* setDeleteBtn(bool enabled = true);
	EditItemWidget* setConformBtn(bool enabled = true);
	EditItemWidget* setCancelBtn(bool enabled = true);

signals:
	void modified();

private slots:
	void on_deletebtn_clicked();

	void on_conformbtn_clicked();

	void on_cancelbtn_clicked();

private:
	UserManager* _userman;
	Ui::editItemWidget *ui;
	ApplyChangeStrategy* apply;
};

#endif // EDITITEMWIDGET_H
