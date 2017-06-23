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

/**
 * @brief Widget to modify and add items, including Currency, Category and Account
 */
class EditItemWidget : public QDialog
{
	Q_OBJECT

public:
	/**
	 * @brief EditItemWidget
	 * @param userman the pointer of UserManager
	 * @param parent the pointer of parent component
	 */
	explicit EditItemWidget(UserManager* userman, QWidget *parent = 0);
	~EditItemWidget();
	/**
	 * @brief getLabelText return the text on the label
	 * @param index 0:label11, 1:label12, 2:label2, 3:label3
	 * @return the specific label
	 */
	QString getLabelText(int index);
	/**
	 * @brief getLineEditText1
	 * @return the LineEditText in the first row
	 */
	QString getLineEditText1();
	/**
	 * @brief getLineEditText2
	 * @return the LineEditText in the second row
	 */
	QString getLineEditText2();
	/**
	 * @brief getComboboxText
	 * @return the combobox on the ui
	 */
	QString getComboboxText();
	/**
	 * @brief getlabelVector
	 * @return the vector of label on ui.(label11, label12, label2, label3)
	 */
	QVector<QLabel*>* getlabelVector();
	/**
	 * @brief setApplyChangeStrategy
	 * @param _apply the strategy to apply to this ui
	 * @return the pointer of EditItemWidget with specific function
	 */
	EditItemWidget* setApplyChangeStrategy(ApplyChangeStrategy* _apply);
	/**
	 * @brief set the names of label on ui
	 * @param labelVector the labels
	 * @param namelist the names of labels
	 * @param visiblelist the visibility of each label
	 * @return the pointer of EditItemWidget with labels having specific names
	 */
	EditItemWidget* setLabelName(QVector<QLabel*> & labelVector, const QStringList& namelist, const QVector<bool>& visiblelist);
	/**
	 * @brief setLineEdit2
	 * @param defaultText set the default text to show on the line edit 2
	 * @param visible set the visibility of this line edit
	 * @return the pointer of EditItemWidget with specific line edit
	 */
	EditItemWidget* setLineEdit2(const QString&defaultText = "", bool visible = true);
	/**
	 * @brief setLineEdit3
	 * @param defaultText set the default text to show on the line edit 3
	 * @param visible set the visibility of this line edit
	 * @return the pointer of EditItemWidget with specific line edit
	 */
	EditItemWidget* setLineEdit3(const QString&defaultText = "", bool visible = true);
	/**
	 * @brief setCurrencyComboBox
	 * @param visible if the combobox is visible
	 * @return the pointer of EditItemWidget with or without combobox
	 */
	EditItemWidget* setCurrencyComboBox(bool visible = true);
	/**
	 * @brief setDeleteBtn
	 * @param enabled if this button can be used
	 * @return the pointer of EditItemWidget with or without delete button
	 */
	EditItemWidget* setDeleteBtn(bool enabled = true);
	/**
	 * @brief setConformBtn
	 * @param enabled if this button can be used
	 * @return the pointer of EditItemWidget with or without conform button
	 */
	EditItemWidget* setConformBtn(bool enabled = true);
	/**
	 * @brief setCancelBtn
	 * @param enabled if this button can be used
	 * @return the pointer of EditItemWidget with or without cancel button
	 */
	EditItemWidget* setCancelBtn(bool enabled = true);
signals:
	/**
	 * @brief modified
	 */
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
