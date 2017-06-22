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
  * @file calendardialog.h
  * @author Zeping Niu <nnznk12@gmail.com>
  * @date 2017.5
  * @brief Header file for class CalendarDialog
  */


#ifndef CALENDARDIALOG_H
#define CALENDARDIALOG_H

#include <QDialog>

namespace Ui {
class CalendarDialog;
}

class CalendarDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CalendarDialog(QWidget *parent = 0);
	QDate getSelectedDate();
	~CalendarDialog();
signals:
	void seletedDateChanged();
    //void dateClicked(QDate);
private slots:
	void on_conformBtn_clicked();

public:
	Ui::CalendarDialog *ui;
};

#endif // CALENDARDIALOG_H
