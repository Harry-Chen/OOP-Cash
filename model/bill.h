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
 * @file   bill.h
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Header file of class Bill
 */

#ifndef BILL_H
#define BILL_H

#include <QString>
#include <QDate>
#include <QDateTime>
#include <date.h>

#include "util/constants.h"
#include "database/tables.h"

using namespace date;
using namespace std::chrono;

/**
 * @brief data model of Bill
 */
class Bill
{
public:
    /**
     * @brief Constructor
     * @param _id ID, can be -1 if unknown
     * @param _from the from Account
     * @param _to the to Account
     * @param _creator ID of User that created the Bill
     * @param _category ID of Category that the Bill belongs to
     * @param _quantity quantity of money (100 times, integer)
     * @param _currency ID of Currency that the Bill uses
     * @param _ctime precise time that the Bill was created
     * @param _finished is the Bill finished
     * @param _date date that the Bill happened
     * @param _note other notes
     */
    Bill(ID _id = -1, ID _from = -1, ID _to = -1,
         ID _creator = -1, ID _category = -1, int _quantity = 0,
         ID _currency = -1, QDateTime _ctime = QDateTime::currentDateTime(),
         bool _finished = true, QDate _date = QDate::currentDate(),
         QString _note = QString());
    ID id;
    ID from;
    ID to;
    ID creator;
    ID category;
    ID currency;
    int quantity;
    QDateTime ctime;
    bool finished;
    QDate date;
    QString note;
    operator std::string();
    static Table::Bill TABLE; ///< for ORM usage
    friend std::ostream& operator<<(std::ostream& os, const Bill& dt);
};

#endif // BILL_H
