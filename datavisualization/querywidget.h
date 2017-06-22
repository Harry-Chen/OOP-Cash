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

/**
 * @brief The QueryWidget class, control the querytab in mainwindow
 */
class QueryWidget : public QWidget
{
    Q_OBJECT
public slots:
    /**
     * @brief setup Calendar
     */
    void setupCalendarFrom();
    void setupCalendarTo();
    /**
     * @brief get date from gui widget
     */
    void setDateFrom();
    void setDateTo();

    /**
     * @brief getField for gui QComboBox
     */
    void getField(int);
    /**
     * @brief do query and plot when "plot" button is clicked
     */
    void Do ();
public:
    /**
     * @brief construct a QueryWidget
     * @param parent
     */
    explicit QueryWidget(QWidget *parent = 0);
    /**
     * @brief set the Userman
     */
    void setUserman( UserManager *);
    ~QueryWidget();
private:


    Ui::QueryWidget *ui;
    CalendarDialog * calendarFrom;
    CalendarDialog * calendarTo;
    Query * pQuery;
    UserManager * pUserManager;

    QList <QString> names;
    QList <ID> ids;
    std::vector<bool> isSelected;///< which items in QListWidget are selecter
    int field;
    QMap <ID, QString> nameMap;

    /**
     * @brief init the widget
     */
    void init();
};

#endif // QUERYWIDGET_H
