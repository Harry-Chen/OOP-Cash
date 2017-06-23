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
 * @file   billlist.cpp
 * @author Zeping Niu <nnznk12@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class BillList
 */


#include "billlist.h"

BillList::BillList(QWidget *parent) : QListWidget(parent)
{
	isAdding = false;
	allFinished = false;
	_scrollBar = this->verticalScrollBar();
	/* when the scroll bar moves, the slot will decide whether to emit signal to load more bills */
	connect(_scrollBar, SIGNAL(valueChanged(int)), this, SLOT(on_scroll_bar_value_changed(int)));
}

void BillList::setIsAddingFalse()
{
	isAdding = false;
}

void BillList::setFinished(bool finished)
{
	allFinished = finished;
}

void BillList::on_scroll_bar_value_changed(int value)
{
	/* the bill list need adding iff the scroll bar rolls to the buttom */
	if(!allFinished && !isAdding && value == _scrollBar->maximum()) {
		isAdding = true;
		emit needAdding();
	}
}
