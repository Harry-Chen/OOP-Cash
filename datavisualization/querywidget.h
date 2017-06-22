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
 * @file   querywidget.h
 * @author 牛辰昊
 * @date   2017.05
 * @brief  Header file of class QueryWidget
 */

#ifndef QUERYWIDGET_H
#define QUERYWIDGET_H

#include <QWidget>
#include <QString>

#include "dao/query.h"
#include "dao/usermanager.h"
#include "dao/currencymanager.h"
#include "dao/accountmanager.h"
#include "dao/categorymanager.h"
#include "dao/billmanager.h"
#include "plot/billsplotsystem.h"
#include "util/database_helper.h"
#include "datavisualization/graphdock.h"
#include "ui/calendardialog.h"

enum Time {byDay, byMonth, byYear};
enum Field { byCategory = 1, byAccountFrom, byAccountTo, byCreator };

namespace Ui {
class QueryWidget;
}

class QueryWidget : public QWidget
{
    Q_OBJECT
public slots:
    void getField(int);
    void Do ();
    void setupCalendarFrom();
    void setupCalendarTo();
    void setDateFrom();
    void setDateTo();
public:
    explicit QueryWidget(QWidget *parent = 0);
    void setUserman( UserManager *);
    ~QueryWidget();
private:
    Ui::QueryWidget *ui;
    Query * pQuery;
    UserManager * pUserManager;
    CalendarDialog * calendarFrom;
    CalendarDialog * calendarTo;
    QList <QString> names;
    QList <ID> ids;
    std::vector<bool> isSelected;
    int field;
    QMap <ID, QString> nameMap;

    void init();
};

#endif // QUERYWIDGET_H
