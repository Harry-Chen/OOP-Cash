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
 * @file   category.h
 * @author Harry Chen <harry-chen@outlook.com>
 * @date   2017.05
 * @brief  Header file of class Category
 */

#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>
#include "util/constants.h"
#include "database/tables.h"

/**
 * @brief data model of Category
 */
class Category
{
public:
    /**
     * @brief Constructor
     * @param _id ID, can be -1 if unknown
     * @param _name name
     * @param _uid ID of user that the Category belongs to, -1 if global
     */
    Category(ID _id = -1, QString _name = QString(), ID _uid = -1);
    ID id;
    QString name;
    ID uid;
    operator std::string();
    static Table::Category TABLE; ///< for ORM usage
    friend std::ostream& operator<<(std::ostream& os, const Category& dt);
};

#endif // CATEGORY_H
