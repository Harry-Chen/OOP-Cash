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
 * @file   calendardialog.cpp
 * @author Zeping Niu <nnznk12@gmail.com>
 * @date   2017.05
 * @brief  Implementation file of class CalendarDialog
 */


#include "calendardialog.h"
#include "ui_calendardialog.h"

CalendarDialog::CalendarDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::CalendarDialog)
{
	ui->setupUi(this);
	/* toss the signal up */
	connect(ui->calendarWidget, SIGNAL(selectionChanged()), this, SIGNAL(seletedDateChanged()));
}

QDate CalendarDialog::getSelectedDate()
{
	return ui->calendarWidget->selectedDate();
}

CalendarDialog::~CalendarDialog()
{
	delete ui;
}

void CalendarDialog::on_conformBtn_clicked()
{
	this->setVisible(false);
}
