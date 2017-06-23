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
  * @file billlist.h
  * @author Zeping Niu <nnznk12@gmail.com>
  * @date 2017.5
  * @brief Header file for class BillList
  */


#ifndef BILLLIST_H
#define BILLLIST_H

#include <QListWidget>
#include <QScrollBar>
#include <QDebug>

/**
 * @brief The BillList class
 */
class BillList : public QListWidget
{
	Q_OBJECT
public:
	/**
	 * @brief BillList
	 * @param parent
	 */
	explicit BillList(QWidget *parent = 0);

public slots:
	/**
	 * @brief setIsAddingFalse
	 * @details set the flag isAdding. when isAdding, truethe BillList will not emit signal.
	 */
	void setIsAddingFalse();
	/**
	 * @brief setFinished
	 * @param finished set the flag allFinished
	 * @details when allFinished the BillList will not emit signal.
	 */
	void setFinished(bool finished);

signals:
	/**
	 * @brief needAdding
	 * @details the signal is emitted iff the BillList needs to be filled.
	 */
	void needAdding();

private slots:
	/**
	 * @brief on_scroll_bar_value_changed
	 * @param value the scroll bar value
	 */
	void on_scroll_bar_value_changed(int value);

private:
	QScrollBar* _scrollBar; ///< the scroll bar of the BillList
	bool isAdding; ///< true when the list widget is adding items
	bool allFinished; ///< true when all the bills are added
};

#endif // BILLLIST_H
