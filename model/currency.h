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
 * @file   currency.h
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Header file of class Currency
 */

#ifndef CURRENCY_H
#define CURRENCY_H

#include <QString>
#include "util/constants.h"
#include "database/tables.h"

/**
 * @brief data model of Currency
 */
class Currency
{
public:
    /**
     * @brief Constructor
     * @param _id ID, can be -1 if unknown
     * @param _uid ID of user that the Currency belongs to
     * @param _name name
     * @param _rate exchaning rate
     */
    Currency(ID _id = -1, ID _uid = -1, QString _name = QString(), unsigned int _rate = 0100);
    ID id;
    ID uid;
    QString name;
    unsigned int rate;
    operator std::string();
    static Table::Currency TABLE; ///< for ORM usage
    friend std::ostream& operator<<(std::ostream& os, const Currency& dt);
};

#endif // CURRENCY_H
